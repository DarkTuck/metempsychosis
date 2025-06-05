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

public:
	UPROPERTY(EditAnywhere)
	TArray<TSoftClassPtr<ATBCEnemyBase>> Enemies;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("EnemiesToSpawn", GetFName());
	}
	UFUNCTION(BlueprintCallable,Category="Data Async Load Helper")
	void RequestAsyncLoad(const UObject* DataOwner);
	UFUNCTION(BlueprintCallable,Category="Data Async Unload Helper")
	void RequestAsyncUnload(const UObject* DataOwner);

	UFUNCTION(BlueprintPure,Category="Data Async Getters")
	TArray<ATBCEnemyBase*> GetEnemies() const;
};
