// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCPartyBase.h"
#include "Engine/DataAsset.h"
#include "PlayerParty.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API UPlayerParty : public UDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ATBCPartyBase>> Parties;
public:
	UFUNCTION(BlueprintCallable)
	TArray<ATBCPartyBase*> GetParties();
};
