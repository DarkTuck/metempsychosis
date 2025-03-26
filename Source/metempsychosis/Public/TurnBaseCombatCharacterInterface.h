// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurnBaseCombatCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTurnBaseCombatCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class METEMPSYCHOSIS_API ITurnBaseCombatCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void BeginTurn();
	void EndTurn();

	void TakeDamage(int DamageAmount);
	void Attack(ITurnBaseCombatCharacterInterface* Target);

	int GetActionPoints() const { return ActionPoints; }
	int Health=100;
	int AttackPower=20;
	int ActionPoints=3;

	void SpendActionPoints(int Amount);
};
