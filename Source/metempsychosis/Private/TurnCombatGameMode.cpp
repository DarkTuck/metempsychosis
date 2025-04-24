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
	//PlayerControllerClass = ATBCPlayerController::StaticClass();
}

void ATurnCombatGameMode::TurnRequest(ACharacter* character)
{
	TurnOrder.AddUnique(character);
	//StartTurn();
}

void ATurnCombatGameMode::StartTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("StartTurn"));
	UE_LOG(LogTemp, Warning, TEXT("bIsSomeonesTurn is %d"), bIsSomeonesTurn);
	if (!bIsSomeonesTurn)
	{
		UE_LOG(LogTemp, Warning, TEXT("there is no ones turn"));
		bIsSomeonesTurn = true;
		if (TurnOrder.Num() > 0)
		{
			UTurnCombatComponent* Character = Cast<UTurnCombatComponent>(Cast<ACharacter>(TurnOrder[0])->GetComponentByClass(UTurnCombatComponent::StaticClass()));
			UE_LOG(LogTemp, Warning, TEXT("TurnOrder.Num() is %d"), TurnOrder.Num());
			UE_LOG(LogTemp, Warning, TEXT("TurnOrder[0] is %s"), *TurnOrder[0]->GetName());
			if (Character)
			{
				UE_LOG(LogTemp,Warning,TEXT("Character Is Not NULL"));
				Character->BeginTurn();
                Character->EndTurnDelegate.BindStatic(&ATurnCombatGameMode::ResetTurn);
                TurnOrder.RemoveAt(0);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Character is NULL"));
			}

			
		}
		else
		{
			ResetTurn();
		}
	}
}
void ATurnCombatGameMode::BeginPlay()
{
	bIsSomeonesTurn=false;
	Super::BeginPlay();
	Camera = UGameplayStatics::GetActorOfClass(this, ATopDownCamera::StaticClass());
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Camera);
	//HUD = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->UIWidget;
	//Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->OnHUDCreated.AddDynamic(this,&ATurnCombatGameMode::InitHUD);
	if (ATBCPlayerController* PC = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		UE_LOG(LogTemp, Warning, TEXT("trying to bind InitHUD"));
		PC->OnHUDCreated.AddDynamic(this, &ATurnCombatGameMode::InitHUD);
		if (PC->UIWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("UIWidget already exist starting InitHUD"));
			InitHUD(PC->UIWidget);
		}
	}
	//TEMP
	UDungeonCombatHandler::bIsPlayerAdvantage=true;
	//END TEMP
}

void ATurnCombatGameMode::InitHUD(UUIwithEvents* NewHUD)
{
	HUD=NewHUD;
	UGameplayStatics::GetAllActorsOfClass(this,ATBCPartyBase::StaticClass(),PartyMembers);
	UGameplayStatics::GetAllActorsOfClass(this,ATBCEnemyBase::StaticClass(),EnemyCharacters);
	for (AActor* const Character : PartyMembers)
	{
		if (ATBCBase* TBase=Cast<ATBCBase>(Character))
		{
			HUD->AddCharacter(TBase);
		}
	}
	CreateTurnOrder();
	//if (UWorld* World=GetWorld())
	//{
	//	World->GetTimerManager().SetTimer(TimerHandle,this,&ATurnCombatGameMode::CreateTurnOrder,0.1f,false);
	//;}
}

void ATurnCombatGameMode::ResetTurn()
{
	bIsSomeonesTurn = false;
	if (TurnOrder.Num() > 0)
	{
		StartTurn();
	}
}

void ATurnCombatGameMode::CreateTurnOrder()
{
	TurnOrder.Empty();
	//find a player character to always start his turn before a party
	AActor** PlayerCharacter = PartyMembers.FindByPredicate([](AActor* Character)
	{
		if (Character)
		{
			ATBCPartyBase* Party = Cast<ATBCPartyBase>(Character);
			if (Party)
			{
				if (UTurnCombatComponent* TurnComp = Party->GetComponentByClass<UTurnCombatComponent>())
				{
					return TurnComp->isPlayer;
				}
			}
		}
		return false;
	});
	if (UDungeonCombatHandler::bIsPlayerAdvantage) //first stars player and his party then enemy
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is first"));
		int8 index=0;
		TurnOrder.Add(Cast<ACharacter>(*PlayerCharacter));
		for (AActor* const Character : PartyMembers)
		{
			index++;
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
			UE_LOG(LogTemp, Warning,TEXT("Character %s added at index: %d"),*Character->GetName(),index-1) ;
			UE_LOG(LogTemp,Warning,TEXT("Array value at current index: %s  current index: %d"),*Cast<ACharacter>(TurnOrder[index-1])->GetName(),index-1);
		}
		index=0;
		for (AActor* const Character : EnemyCharacters)
		{
			index++;
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
			UE_LOG(LogTemp, Warning,TEXT("Enemy %s added at index: %d"),*Character->GetName(),index-1) ;
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



void ATurnCombatGameMode::TurnOrderUpdate(ACharacter* Character)
{
	TurnOrder.Insert(Character, 0);
}
