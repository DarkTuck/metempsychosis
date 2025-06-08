// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCombatHandler.h"
#include "NPC.h"
#include "GameFramework/Actor.h"
#include "DungeonCombatActor.generated.h"
UCLASS()
class METEMPSYCHOSIS_API ADungeonCombatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonCombatActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY()
	//Map<int8,TSoftObjectPtr<ANPC>> NPCsMap;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Enemies;
	UPROPERTY()
	UDungeonCombatHandler* DungeonCombatHandler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	FString BattleScene;
	
	UFUNCTION()
	void StartCombat();

	void EnableEnemies();
	void SaveEnemies() const;
};
