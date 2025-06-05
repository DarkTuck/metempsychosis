// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatGameMode.h"

#include "DungeonCombatHandler.h"
#include "TBCEnemyBase.h"
#include "TBCPartyBase.h"
#include "TBCPlayerController.h"
#include "TopDownCamera.h"
#include "GameFramework/Character.h"
#include "TurnCombatComponent.h"
#include "Kismet/GameplayStatics.h"

TArray<ACharacter*> ATurnCombatGameMode::TurnOrder;
bool ATurnCombatGameMode::bIsSomeonesTurn = false;
AActor* ATurnCombatGameMode::Camera = nullptr;
UUIwithEvents* ATurnCombatGameMode::HUD = nullptr;


ATurnCombatGameMode::ATurnCombatGameMode()
{
	PlayerControllerClass = ATBCPlayerController::StaticClass();
}

void ATurnCombatGameMode::TurnRequest(ACharacter* Character)
{
	TurnOrder.AddUnique(Character);
	StartTurn();
}

void ATurnCombatGameMode::StartTurn()
{
	UE_LOG(LogTemp, Log, TEXT("StartTurn"));
	if (!bIsSomeonesTurn)
	{
		UE_LOG(LogTemp, Log, TEXT("there is no ones turn"));
		bIsSomeonesTurn = true;
		if (TurnOrder.Num() > 0)
		{
			if (UTurnCombatComponent* Character = Cast<UTurnCombatComponent>(Cast<ACharacter>(TurnOrder[0])->GetComponentByClass(UTurnCombatComponent::StaticClass())))
			{
				UE_LOG(LogTemp,Log,TEXT("Character Is Not NULL"));
				Character->BeginTurn();
                Character->EndTurnDelegate.BindStatic(&ATurnCombatGameMode::ResetTurn);
                TurnOrder.RemoveAt(0);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Character is NULL"));
			}

			
		}
		else
		{
			GEngine->GameViewport->GetWorld()->GetAuthGameMode<ATurnCombatGameMode>()->CreateTurnOrder();
			ResetTurn();
		}
	}
}
void ATurnCombatGameMode::BeginPlay()
{
	TArray<AActor*> TempSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattlePosition::StaticClass(), TempSpawnPoints );
	for (AActor* const SpawnPoint : TempSpawnPoints)
	{
		SpawnPoints.Add(Cast<ABattlePosition>(SpawnPoint));
	}
	PartyMembers=UDungeonCombatHandler::Parties;
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay (GameMode): UDungeonCombatHandler::Parties.Num() = %d"), 
	   UDungeonCombatHandler::Parties.Num());
	EnemyCharacters=UDungeonCombatHandler::EniemiesParty;
	bIsSomeonesTurn=false;
	Super::BeginPlay();
	Camera = UGameplayStatics::GetActorOfClass(this, ATopDownCamera::StaticClass());
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Camera);
	//HUD = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->UIWidget;
	//Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->OnHUDCreated.AddDynamic(this,&ATurnCombatGameMode::InitHUD);
	if (ATBCPlayerController* PC = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		UE_LOG(LogTemp, Log, TEXT("trying to bind InitHUD"));
		PC->OnHUDCreated.AddDynamic(this, &ATurnCombatGameMode::InitHUD);
		if (PC->UIWidget)
		{
			UE_LOG(LogTemp, Log, TEXT("UIWidget already exist starting InitHUD"));
			InitHUD(PC->UIWidget);
		}
	}
	//TEMP
	UDungeonCombatHandler::bIsPlayerAdvantage=true;
	//END TEMP
}

void ATurnCombatGameMode::CharacterDies(const bool bIsParty, ACharacter* Character)
{
	if (bIsParty)
	{
		ATBCPartyBase* PartyCharacter = Cast<ATBCPartyBase>(Character);
		PartyMembers.Remove(PartyCharacter);
		if (PartyMembers.Num() <= 0)
		{
			UDungeonCombatHandler::EndCombat(false);
		}
	}
	else
	{
		ATBCEnemyBase* EnemyCharacter = Cast<ATBCEnemyBase>(Character);
		EnemyCharacters.Remove(EnemyCharacter);
		if (EnemyCharacters.Num() <= 0)
		{
			UDungeonCombatHandler::EndCombat(true);
		}
	}
}

void ATurnCombatGameMode::InitHUD(UUIwithEvents* NewHUD)
{
	Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->OnHUDCreated.RemoveDynamic(this,&ATurnCombatGameMode::InitHUD);
	HUD=NewHUD;
	//UGameplayStatics::GetAllActorsOfClass(this,ATBCPartyBase::StaticClass(),PartyMembers);
	//GameplayStatics::GetAllActorsOfClass(this,ATBCEnemyBase::StaticClass(),EnemyCharacters);
	int8 EnemyIndex=0;
	int8 PlayerIndex=0;
	for (int8 i = 0;i<SpawnPoints.Num();i++)
	{
		if (SpawnPoints[i]->bIsEnemy)
		{
			if (EnemyIndex<4)
         	{
         		SpawnPoints[i]->Character = EnemyCharacters[EnemyIndex]->GetClass();
				EnemyIndex++;	
         	}

		}
		else
		{
			if (PlayerIndex<4)
			{
				SpawnPoints[i]->Character=PartyMembers[PlayerIndex]->GetClass();
                PlayerIndex++;
			}
		}
	}
	SpawnActors.Broadcast();
	TArray<AActor*> TempPartyMembers;
	TArray<AActor*> TempEnemies;
	PartyMembers.Empty();
	EnemyCharacters.Empty();
	UGameplayStatics::GetAllActorsOfClass(this,ATBCPartyBase::StaticClass(),TempPartyMembers);
	UGameplayStatics::GetAllActorsOfClass(this,ATBCEnemyBase::StaticClass(),TempEnemies);
	for (AActor* const Character : TempPartyMembers)
	{
		PartyMembers.Add(Cast<ATBCPartyBase>(Character));
	}
	for (AActor* const Character : TempEnemies)
	{
		EnemyCharacters.Add(Cast<ATBCEnemyBase>(Character));
	}
	CreateTurnOrder();
	//if (UWorld* World=GetWorld())
	//{
	//	World->GetTimerManager().SetTimer(TimerHandle,this,&ATurnCombatGameMode::CreateTurnOrder,0.1f,false);
	//;}
}

// void ATurnCombatGameMode::InitHUD(UUIwithEvents* NewHUD)
// {
//     // 0) Usuwamy delegata, żeby nie odpalać InitHUD ponownie
//     Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))
//         ->OnHUDCreated.RemoveDynamic(this, &ATurnCombatGameMode::InitHUD);
//
//     // 1) Zapisujemy wskaźnik do HUD-a
//     HUD = NewHUD;
//
//     // 2) Logujemy raz rozmiary tablic, żeby było widać, czy cokolwiek w nich siedzi
//     UE_LOG(LogTemp, Warning, TEXT("InitHUD: PartyMembers.Num() = %d; EnemyCharacters.Num() = %d"),
//            PartyMembers.Num(), EnemyCharacters.Num());
//
//     // 3) Jeżeli obie tablice są puste, można wyjść wcześniej
//     if (PartyMembers.Num() == 0 && EnemyCharacters.Num() == 0)
//     {
//         UE_LOG(LogTemp, Error, TEXT("InitHUD: obie tablice (PartyMembers i EnemyCharacters) są puste → wychodzę"));
//         return;
//     }
//
//     // 4) Przygotowujemy liczniki jako int8
//     int8 EnemyIndex = 0;
//     int8 PlayerIndex = 0;
//
//     // 5) Iterujemy po 8 potencjalnych spawn-pointach (zakładam, że masz dokładnie 8 elementów w SpawnPoints)
//     for (int8 i = 0; i < 8; ++i)
//     {
//         // 5a) Sprawdźmy, czy SpawnPoints[i] jest poprawny
//         if (!SpawnPoints.IsValidIndex(i) || SpawnPoints[i] == nullptr)
//         {
//             UE_LOG(LogTemp, Warning, TEXT("InitHUD: brak lub nullptr w SpawnPoints[%d], pomijam"), i);
//             continue;
//         }
//
//         // 5b) Jeżeli to spawn dla wroga:
//         if (SpawnPoints[i]->bIsEnemy)
//         {
//             // Sprawdzamy, czy w EnemyCharacters jest coś pod indeksem EnemyIndex
//             if (EnemyCharacters.IsValidIndex((int32)EnemyIndex) && EnemyCharacters[EnemyIndex] != nullptr)
//             {
//                 // Przypisujemy klasę instancji actora
//                 SpawnPoints[i]->Character = EnemyCharacters[EnemyIndex]->GetClass();
//                 UE_LOG(LogTemp, Log, TEXT("InitHUD: przypisano EnemyCharacters[%d] do SpawnPoints[%d] → %s"),
//                        EnemyIndex, i, *EnemyCharacters[EnemyIndex]->GetName());
//
//                 // Zwiększamy licznik wrogów
//                 EnemyIndex++;
//             }
//             else
//             {
//                 UE_LOG(LogTemp, Error, TEXT(
//                     "InitHUD: brak kolejnego elementu w EnemyCharacters pod indeksem %d"),
//                     EnemyIndex);
//             }
//         }
//         else
//         {
//             // 5c) To jest spawn dla gracza
//             if (PartyMembers.IsValidIndex((int32)PlayerIndex) && PartyMembers[PlayerIndex] != nullptr)
//             {
//                 // Przypisujemy klasę instancji aktora gracza
//                 SpawnPoints[i]->Character = PartyMembers[PlayerIndex]->GetClass();
//                 UE_LOG(LogTemp, Log, TEXT("InitHUD: przypisano PartyMembers[%d] do SpawnPoints[%d] → %s"),
//                        PlayerIndex, i, *PartyMembers[PlayerIndex]->GetName());
//
//                 // Dodajemy instancję do HUD-a
//                 ATBCBase* BasePawn = Cast<ATBCBase>(PartyMembers[PlayerIndex]);
//                 if (BasePawn)
//                 {
//                     HUD->AddCharacter(BasePawn);
//                     UE_LOG(LogTemp, Log, TEXT("InitHUD: HUD->AddCharacter dla PartyMembers[%d]"), PlayerIndex);
//                 }
//                 else
//                 {
//                     UE_LOG(LogTemp, Warning, TEXT(
//                         "InitHUD: PartyMembers[%d] nie jest ATBCBase (nullptr po cast), pomijam dodanie do HUD"),
//                         PlayerIndex);
//                 }
//
//                 // Zwiększamy licznik graczy
//                 PlayerIndex++;
//             }
//             else
//             {
//                 UE_LOG(LogTemp, Error, TEXT(
//                     "InitHUD: brak kolejnego elementu w PartyMembers pod indeksem %d"),
//                     PlayerIndex);
//             }
//         }
//     }
//
//     // 6) Na końcu emitujemy event o spawnie i tworzymy kolejność tur
//     SpawnActors.Broadcast();
//   CreateTurnOrder();
// }



void ATurnCombatGameMode::ResetTurn()
{
	bIsSomeonesTurn = false;
	StartTurn();
}

void ATurnCombatGameMode::CreateTurnOrder()
{
	TurnOrder.Empty();
	//find a player character to always start his turn before a party
	ATBCPartyBase** PlayerCharacter = PartyMembers.FindByPredicate([](ATBCPartyBase* Character)
	{
		if (Character)
		{
			if (const ATBCBase* Party = Cast<ATBCBase>(Character))
			{
				return Party->bIsPlayer;
			}
		}
		return false;
	});
	if (UDungeonCombatHandler::bIsPlayerAdvantage) //first stars player and his party then enemy
	{
		UE_LOG(LogTemp, Log, TEXT("Player is first"));
		int8 Index=0;
		if (!PlayerCharacter)
		{
			UDungeonCombatHandler::EndCombat(false);
		}
		TurnOrder.Add(Cast<ACharacter>(*PlayerCharacter));
		for (AActor* const Character : PartyMembers)
		{
			Index++;
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
			UE_LOG(LogTemp, Log,TEXT("Character %s added at index: %d"),*Character->GetName(),Index-1) ;
			UE_LOG(LogTemp,Log,TEXT("Array value at current index: %s  current index: %d"),*Cast<ACharacter>(TurnOrder[Index-1])->GetName(),Index-1);
		}
		Index=0;
		for (AActor* const Character : EnemyCharacters)
		{
			Index++;
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
			UE_LOG(LogTemp, Log,TEXT("Enemy %s added at index: %d"),*Character->GetName(),Index-1) ;
		}
	}
	else //first starts enemy then player and his party
	{
		UE_LOG(LogTemp,Warning,TEXT("Enemy is first"));
		for (AActor* const Character : EnemyCharacters)
		{
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
		}
		TurnOrder.Add(Cast<ACharacter>(*PlayerCharacter));
		for (AActor* const Character : PartyMembers)
		{
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
		}
	}
	StartTurn();
}

// void ATurnCombatGameMode::CreateTurnOrder()
// {
//     // 1) Wyczyśćmy starą kolejkę
//     TurnOrder.Empty();
//
// 	// --- DODATKOWA DIAGNOSTYKA ---
// 	UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: wchodzę w funkcję, PartyMembers.Num() = %d"), PartyMembers.Num());
// 	for (int32 idx = 0; idx < PartyMembers.Num(); ++idx)
// 	{
// 		ATBCPartyBase* Member = PartyMembers[idx];
// 		if (Member)
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("  PartyMembers[%d] = %s"), idx, *Member->GetName());
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("  PartyMembers[%d] = nullptr"), idx);
// 		}
// 	}
// 	// --------------------------------
// 	
//     // 2) Znajdźmy „głównego” gracza w PartyMembers (ten z bIsPlayer == true)
// 	ATBCPartyBase* FoundPlayer = nullptr;
// 	for (int8 i = 0; i < PartyMembers.Num(); ++i)
// 	{
// 		ATBCPartyBase* Member = PartyMembers[i];
// 		if (Member)
// 		{
// 			if (ATBCBase* Party = Cast<ATBCBase>(Member))
// 			{
// 				if (Party->bIsPlayer)
// 				{
// 					FoundPlayer = Member;
// 					UE_LOG(LogTemp, Log, TEXT("CreateTurnOrder: znaleziono głównego gracza: %s (PartyMembers[%d])"),
// 						   *Party->GetName(), i);
// 					break;
// 				}
// 			}
// 		}
// 	}
//
//     // 3) Jeżeli włączona jest przewaga gracza, to zaczynamy od gracza
//     if (UDungeonCombatHandler::bIsPlayerAdvantage)
//     {
//         UE_LOG(LogTemp, Log, TEXT("CreateTurnOrder: Player is first"));
//
//         // 3a) Jeśli nie znaleźliśmy żadnego gracza, kończymy walkę
//         if (!FoundPlayer)
//         {
//             UE_LOG(LogTemp, Error, TEXT("CreateTurnOrder: nie znaleziono głównego gracza → kończę Combat"));
//             UDungeonCombatHandler::EndCombat(false);
//             return;
//         }
//
//         // 3b) Dodajmy najpierw „głównego” gracza
//         {
//             ACharacter* AsChar = Cast<ACharacter>(FoundPlayer);
//             if (AsChar)
//             {
//                 TurnOrder.Add(AsChar);
//                 UE_LOG(LogTemp, Log, TEXT("  → Dodano FoundPlayer: %s na pozycji 0"), *AsChar->GetName());
//             }
//             else
//             {
//                 UE_LOG(LogTemp, Error, TEXT("CreateTurnOrder: FoundPlayer nie jest ACharacter!"));
//             }
//         }
//
//         // 3c) Dodajemy pozostałych członków drużyny (wszyscy poza FoundPlayer)
//         {
//             int8 Index = 1;
//             for (int8 i = 0; i < PartyMembers.Num(); ++i)
//             {
//                 ATBCPartyBase* Member = PartyMembers[i];
//                 if (Member && Member != FoundPlayer)
//                 {
//                     ACharacter* AsChar = Cast<ACharacter>(Member);
//                     if (AsChar)
//                     {
//                         TurnOrder.Add(AsChar);
//                         UE_LOG(LogTemp, Log, TEXT("  → Dodano PartyMembers[%d] = %s na pozycji %d"),
//                                i, *AsChar->GetName(), Index);
//                         ++Index;
//                     }
//                     else
//                     {
//                         UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: PartyMembers[%d] (%s) nie jest ACharacter, pomijam"),
//                                i, *Member->GetName());
//                     }
//                 }
//             }
//         }
//
//         // 3d) Na końcu dorzućmy wrogów
//         {
//             int8 Index = TurnOrder.Num();
//             for (int8 j = 0; j < EnemyCharacters.Num(); ++j)
//             {
//                 ATBCEnemyBase* Enemy = EnemyCharacters[j];
//                 if (Enemy)
//                 {
//                     ACharacter* AsChar = Cast<ACharacter>(Enemy);
//                     if (AsChar)
//                     {
//                         TurnOrder.Add(AsChar);
//                         UE_LOG(LogTemp, Log, TEXT("  → Dodano EnemyCharacters[%d] = %s na pozycji %d"),
//                                j, *AsChar->GetName(), Index);
//                         ++Index;
//                     }
//                     else
//                     {
//                         UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: EnemyCharacters[%d] (%s) nie jest ACharacter, pomijam"),
//                                j, *Enemy->GetName());
//                     }
//                 }
//             }
//         }
//     }
//     // 4) W przeciwnym razie – najpierw wrogowie, potem gracz, potem reszta drużyny
//     else
//     {
//         UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: Enemy is first"));
//
//         // 4a) Dodajemy najpierw wrogów
//         {
//             int8 Index = 0;
//             for (int8 j = 0; j < EnemyCharacters.Num(); ++j)
//             {
//                 ATBCEnemyBase* Enemy = EnemyCharacters[j];
//                 if (Enemy)
//                 {
//                     ACharacter* AsChar = Cast<ACharacter>(Enemy);
//                     if (AsChar)
//                     {
//                         TurnOrder.Add(AsChar);
//                         UE_LOG(LogTemp, Log, TEXT("  → Dodano EnemyCharacters[%d] = %s na pozycji %d"),
//                                j, *AsChar->GetName(), Index);
//                         ++Index;
//                     }
//                     else
//                     {
//                         UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: EnemyCharacters[%d] (%s) nie jest ACharacter, pomijam"),
//                                j, *Enemy->GetName());
//                     }
//                 }
//             }
//
//             // 4b) Dodajemy „głównego” gracza zaraz po wrogach (jeśli istnieje)
//             if (FoundPlayer)
//             {
//                 ACharacter* AsChar = Cast<ACharacter>(FoundPlayer);
//                 if (AsChar)
//                 {
//                     TurnOrder.Add(AsChar);
//                     UE_LOG(LogTemp, Log, TEXT("  → Dodano FoundPlayer: %s na pozycji %d"),
//                            *AsChar->GetName(), Index);
//                     ++Index;
//                 }
//                 else
//                 {
//                     UE_LOG(LogTemp, Error, TEXT("CreateTurnOrder: FoundPlayer nie jest ACharacter!"));
//                 }
//             }
//             else
//             {
//                 UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: brak FoundPlayer, pominąłem dodanie gracza"));
//             }
//
//             // 4c) Dodajemy resztę drużyny (z wyłączeniem już dodanego FoundPlayer)
//             for (int8 i = 0; i < PartyMembers.Num(); ++i)
//             {
//                 ATBCPartyBase* Member = PartyMembers[i];
//                 if (Member && Member != FoundPlayer)
//                 {
//                     ACharacter* AsChar = Cast<ACharacter>(Member);
//                     if (AsChar)
//                     {
//                         TurnOrder.Add(AsChar);
//                         UE_LOG(LogTemp, Log, TEXT("  → Dodano PartyMembers[%d] = %s na pozycji %d"),
//                                i, *AsChar->GetName(), Index);
//                         ++Index;
//                     }
//                     else
//                     {
//                         UE_LOG(LogTemp, Warning, TEXT("CreateTurnOrder: PartyMembers[%d] (%s) nie jest ACharacter, pomijam"),
//                                i, *Member->GetName());
//                     }
//                 }
//             }
//         }
//     }
//
//     // 5) Startujemy turę
//     StartTurn();
// }


void ATurnCombatGameMode::TurnOrderUpdate(ACharacter* Character)
{
	TurnOrder.Insert(Character, 0);
}
