// Fill out your copyright notice in the Description page of Project Settings.


#include "TBCBase.h"

// Sets default values
ATBCBase::ATBCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UTurnCombatComponent>(TEXT("CombatComponent"));

}

// Called when the game starts or when spawned
void ATBCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATBCBase::OnConstruction(const FTransform& Transform)
{
	//CombatComponent->Health = HP;
}

// Called every frame
void ATBCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATBCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

