// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatGameMode.h"
#include "GameFramework/Character.h"
#include "TurnCombatCharacter.h"

TArray<ACharacter*> ATurnCombatGameMode::TurnOrder;
bool ATurnCombatGameMode::bIsSomeonesTurn = false;

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

void ATurnCombatGameMode::ResetTurn()
{
	bIsSomeonesTurn = false;
	if (TurnOrder.Num() > 0)
	{
		StartTurn();
	}
}
