// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCombatActor.h"
//#include ""
#include "DungeonCombatHandler.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADungeonCombatActor::ADungeonCombatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UDungeonCombatHandler::OnStartCombat.AddDynamic(this,&ADungeonCombatActor::StartCombat);
}

// Called when the game starts or when spawned
void ADungeonCombatActor::BeginPlay()
{
	Super::BeginPlay();
	UDungeonCombatHandler::MapName=UGameplayStatics::GetCurrentLevelName(GetWorld());
	
}

// Called every frame
void ADungeonCombatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ADungeonCombatActor::StartCombat()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(BattleScene));
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Trigger Fight");
}
