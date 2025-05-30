// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBattleControler.h"
#include "TBCBase.h"
#include "TBCEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API ATBCEnemyBase : public ATBCBase
{
	GENERATED_BODY()
	ATBCEnemyBase();
	UPROPERTY()
	UAIBattleControler* Controler;
	
};
