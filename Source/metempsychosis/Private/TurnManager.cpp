// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"

// Sets default values
ATurnManager::ATurnManager(): CurrentCharacter(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATurnManager::StartTurn(UTurnCombatCharacter* Character)
{
	CurrentCharacter = Character;
	CurrentCharacter->BeginTurn();
}

void ATurnManager::EndTurn() const
{
	if (CurrentCharacter)
	{
		CurrentCharacter->EndTurn();
	}
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

