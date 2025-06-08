// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCombatActor.h"
#include "TempSave.h"
#include "DungeonCombatHandler.h"
#include "NPC.h"
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
	const UWorld* World = GetWorld();
	DungeonCombatHandler = Cast<UDungeonCombatHandler>(UGameplayStatics::GetGameInstance(World));
	Super::BeginPlay();
	UDungeonCombatHandler::MapName=UGameplayStatics::GetCurrentLevelName(World);
	//UGameplayStatics::GetAllActorsOfClass(World,ANPC::StaticClass(),Enemies);
	EnableEnemies();
	
}

// Called every frame
void ADungeonCombatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ADungeonCombatActor::StartCombat()
{
	//if (UTempSave* SaveGameInstance=Cast<UTempSave>(UGameplayStatics::CreateSaveGameObject(UTempSave::StaticClass())))
	//{
		//if (UGameplayStatics::SaveGameToMemory(SaveGameInstance,UDungeonCombatHandler::OutSaveData))
		//{
			//save game
		//}
	//}
	SaveEnemies();
	UGameplayStatics::OpenLevel(GetWorld(), FName(BattleScene));
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Trigger Fight");
}

void ADungeonCombatActor::EnableEnemies()
{
	if (const TMap<int8,bool>& NPCsSpawnMap = DungeonCombatHandler->NPCsSpawnMap; NPCsSpawnMap.Num() == Enemies.Num())
	{
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(UDungeonCombatHandler::PlayerSpawnLocation);
		for (int i = 0; i < NPCsSpawnMap.Num(); i++)
		{
			Enemies[i]->SetActorHiddenInGame(NPCsSpawnMap[i]);
		}
	}
	else
	{
		for (AActor* Enemy : Enemies)
		{
			Enemy->SetActorHiddenInGame(false);
		}
	}
	DungeonCombatHandler->NPCsSpawnMap.Empty();
}

void ADungeonCombatActor::SaveEnemies() const
{
	for (int i = 0; i < Enemies.Num(); i++)
	{
		const ANPC* NPC = Cast<ANPC>(Enemies[i]);
		UE_LOG(LogTemp, Log, TEXT("SaveEnemies: %s"), *NPC->GetName());
		const bool bIsDisabled = NPC->disableOnSpawn;
		DungeonCombatHandler->NPCsSpawnMap.Add(i, bIsDisabled);
	}
}
