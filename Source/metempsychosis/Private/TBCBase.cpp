// Fill out your copyright notice in the Description page of Project Settings.


#include "TBCBase.h"

#include "TurnCombatGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATBCBase::ATBCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UTurnCombatComponent>(TEXT("CombatComponent"));
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;

}

int ATBCBase::CalculateDamage(const int Damage) const
{
	return Damage-DamageReduction;
}

void ATBCBase::GetDamaged(const int Damage)
{
	HP-=Damage;
	RefreshUI.Broadcast();
	UE_LOG(LogTemp,Log,TEXT("CurentHP %d"),HP);
	if (HP<=0)
	{
		Cast<ATurnCombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->CharacterDies(!bIsEnemyCharacter,this);
		Destroy();
	}
	
}


void ATBCBase::SendAttackCommand(ACharacter* Target)
{
	if (CombatComponent)
	{
		CombatComponent->AttackCommand(Target);
	}
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

