// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombatActor.h"

#include "TurnBaseCombat.h"

// Sets default values
ATurnBaseCombatActor::ATurnBaseCombatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UTurnBaseCombat::StartCombatDelegate.AddDynamic(this,&ATurnBaseCombatActor::StartCombat);
}

// Called when the game starts or when spawned
void ATurnBaseCombatActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnBaseCombatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnBaseCombatActor::ChangeCharacter() const
{
	TurnManager->StartTurn(UTurnBaseCombat::NextCharacter());
}

void ATurnBaseCombatActor::StartCombat()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(BattleScene));
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Trigger Fight");
}

