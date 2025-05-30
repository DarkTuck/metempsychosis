// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBattleControler.h"
#include "TBCBase.h"
#include "TBCPartyBase.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API ATBCPartyBase : public ATBCBase
{
	GENERATED_BODY()
	ATBCPartyBase();
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY()
	UAIBattleControler* Controler;
};
