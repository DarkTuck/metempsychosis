// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCEnemyBase.h"
#include "TBCPartyBase.h"
#include "DungeonCombatHandler.generated.h"


/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnStartCombat);
UCLASS()
class METEMPSYCHOSIS_API UDungeonCombatHandler : public UGameInstance
{
	/*This was meant to be only a static class used for easy communication between the dungeon and the fight
	 *that derived from my misunderstanding of c++ after switching from c# and unity (Was aiming for singleton).
	 *If my thinking is correct, this should be constructed and handled differently.
	 * Now it is what it is, a probably bad and primitive save and communication system.
	 * WHO NEEDS MEMORY ANYWAY, RIGHT?
	 */ 
	GENERATED_BODY()
public:
	UDungeonCombatHandler();
	static void StarCombat(bool bIsPlayer, const TArray<ATBCEnemyBase*>& Party);
	static FOnStartCombat OnStartCombat;
	static bool bIsPlayerAdvantage;
	static void EndCombat(bool bPlayerWon);
	static FString MapName;
	static TArray<ATBCEnemyBase*> EnemiesParty;
	static TArray<ATBCPartyBase*> Parties;
	static bool bCanStartCombat;
	virtual void StartGameInstance() override;
	//static TArray<uint8> OutSaveData;
	TMap<int8,bool> NPCsSpawnMap;
	void SetIndex(const int8 Index,const bool bValue);
	static FVector PlayerSpawnLocation;
};
