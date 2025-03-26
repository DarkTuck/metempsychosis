// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombatCharacterInterface.h"


// Add default functionality here for any ITurnBaseCombatCharacterInterface functions that are not pure virtual.
void ITurnBaseCombatCharacterInterface::BeginTurn()
{
	//Reset or refill action points at the beginning of the turn
	ActionPoints = 3;
}

void ITurnBaseCombatCharacterInterface::EndTurn()
{
	//TODO
}

void ITurnBaseCombatCharacterInterface::TakeDamage(int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		//TODO
	}
}

void ITurnBaseCombatCharacterInterface::Attack(ITurnBaseCombatCharacterInterface* Target)
{
	if (ActionPoints > 0)
	{
		Target->TakeDamage(AttackPower);
		SpendActionPoints(1);
	}
}

void ITurnBaseCombatCharacterInterface::SpendActionPoints(int Amount)
{
	ActionPoints -= Amount;
}
