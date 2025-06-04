// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCEnemyBase.h"
#include "Engine/DataAsset.h"
#include "EnemiesToSpawn.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API UEnemiesToSpawn : public UPrimaryDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ATBCEnemyBase>> Enemies;
public:
	UFUNCTION(BlueprintCallable)
	TArray<ATBCEnemyBase*> GetEnemies();
};
