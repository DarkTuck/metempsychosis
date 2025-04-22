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
	if (!bIsSomeonesTurn)
	{
		bIsSomeonesTurn = true;
		if (TurnOrder.Num() > 0)
		{
			UTurnCombatComponent* Character = Cast<UTurnCombatComponent>(TurnOrder[0]);
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

void ATurnCombatGameMode::CreateTurnOrder()
{
	TurnOrder.Empty();
	//find a player character to always start his turn before a party
	AActor** PlayerCharacter = PartyMembers.FindByPredicate([](const ACharacter* Character)
	{
		if (UTurnCombatComponent* TurnComp=Character->GetComponentByClass<UTurnCombatComponent>())
		{
			return TurnComp->isPlayer;
		}
		return false;
	});
	if (UDungeonCombatHandler::bIsPlayerAdvantage) //first stars player and his party then enemy
	{
		TurnOrder.Add(Cast<ACharacter>(*PlayerCharacter));
		for (AActor* const Character : PartyMembers)
		{
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
		}
		for (AActor* const Character : EnemyCharacters)
		{
			TurnOrder.AddUnique(Cast<ACharacter>(Character));
		}
	}
	else //first starts enemy then player and his party
	{
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
