// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatComponent.h"

#include <filesystem>

#include "DungeonCombatHandler.h"
#include "TurnCombatGameMode.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UTurnCombatComponent::UTurnCombatComponent(): Character(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurnCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurnCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurnCombatComponent::BeginTurn()
{
	//Reset or refill action points at the beginning of the turn
	//ActionPoints = 3;
}

void UTurnCombatComponent::EndTurn() const
{
	EndTurnDelegate.ExecuteIfBound();
}
/*
void UTurnCombatComponent::TakeDamage(const int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		UTurnBaseCombat::AddCharacter(this,bIsFriendly);
	}
}


void UTurnCombatComponent::Attack(UTurnCombatComponent* Target)
{
	//if (ActionPoints > 0)
	//{
		//Target->TakeDamage(AttackPower);
		//SpendActionPoints(1);
	//}
}
*/
void UTurnCombatComponent::RequestTurn() const
{
	ATurnCombatGameMode::TurnRequest(Character);
}

void UTurnCombatComponent::SpendActionPoints(const int Amount)
{
	//ActionPoints -= Amount;
}

void UTurnCombatComponent::BeginCombat()
{
	Character=Cast<ACharacter>(GetOwner());
	BattleTransform=Character->GetActorTransform();
	
}

