// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatGameMode.h"

#include "TBCEnemyBase.h"
#include "TBCPartyBase.h"
#include "TBCPlayerController.h"
#include "TopDownCamera.h"
#include "GameFramework/Character.h"
#include "TurnCombatCharacter.h"
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
	StartTurn();
}

void ATurnCombatGameMode::StartTurn()
{
	if (!bIsSomeonesTurn)
	{
		bIsSomeonesTurn = true;
		if (TurnOrder.Num() > 0)
		{
			UTurnCombatCharacter* Character = Cast<UTurnCombatCharacter>(TurnOrder[0]);
			Character->BeginTurn();
			Character->EndTurnDelegate.BindStatic(&ATurnCombatGameMode::ResetTurn);
			TurnOrder.RemoveAt(0);
			
		}
		else
		{
			ResetTurn();
		}
	}
}
void ATurnCombatGameMode::BeginPlay()
{
	Super::BeginPlay();
	Camera = UGameplayStatics::GetActorOfClass(this, ATopDownCamera::StaticClass());
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Camera);
	//HUD = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->UIWidget;
	//Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->OnHUDCreated.AddDynamic(this,&ATurnCombatGameMode::InitHUD);
	ATBCPlayerController* PC = Cast<ATBCPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Próba bindowania InitHUD"));
		PC->OnHUDCreated.AddDynamic(this, &ATurnCombatGameMode::InitHUD);
		if (PC->UIWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("UIWidget już istnieje, wywołuję InitHUD bezpośrednio"));
			InitHUD(PC->UIWidget);
		}
	}

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
}

void ATurnCombatGameMode::ResetTurn()
{
	bIsSomeonesTurn = false;
	if (TurnOrder.Num() > 0)
	{
		StartTurn();
	}
}
