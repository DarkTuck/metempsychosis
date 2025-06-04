// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCEnemyBase.h"
#include "TBCPartyBase.h"
#include "DungeonCombatHandler.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartCombat);
UCLASS()
class METEMPSYCHOSIS_API UDungeonCombatHandler : public UObject
{
	GENERATED_BODY()
public:
	UDungeonCombatHandler();
	static void StarCombat(bool bIsPlayer, const TArray<ATBCEnemyBase*>& Party);
	static FOnStartCombat OnStartCombat;
	static bool bIsPlayerAdvantage;
	static void EndCombat(bool bPlayerWon);
	static FString MapName;
	static TArray<ATBCEnemyBase*> EniemiesParty;
	static TArray<ATBCPartyBase*> Parties;
protected:
	static FVector PlayerSpawnLocation;
};
