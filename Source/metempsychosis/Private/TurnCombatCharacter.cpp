// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatCharacter.h"

// Sets default values for this component's properties
UTurnCombatCharacter::UTurnCombatCharacter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurnCombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurnCombatCharacter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurnCombatCharacter::BeginTurn()
{
	//Reset or refill action points at the beginning of the turn
	ActionPoints = 3;
}

void UTurnCombatCharacter::EndTurn()
{
	//TODO
}

void UTurnCombatCharacter::TakeDamage(int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		//TODO
	}
}


void UTurnCombatCharacter::Attack(UTurnCombatCharacter* Target)
{
	if (ActionPoints > 0)
	{
		Target->TakeDamage(AttackPower);
		SpendActionPoints(1);
	}
}

void UTurnCombatCharacter::SpendActionPoints(int Amount)
{
	ActionPoints -= Amount;
}

