// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattlePosition.h"
#include "TBCEnemyBase.h"
#include "TBCPartyBase.h"
#include "UIwithEvents.h"
#include "GameFramework/GameModeBase.h"
#include "TurnCombatGameMode.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(SpawnActors)
UCLASS()
class METEMPSYCHOSIS_API ATurnCombatGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATurnCombatGameMode();
	static void TurnRequest(ACharacter* const Character);
	static void StartTurn();
	virtual void BeginPlay() override;
	void CharacterDies(const bool bIsParty,ACharacter* const Character);
	void RegisterCharacter(ATBCBase* Character,const bool bIsParty);
	UPROPERTY(BlueprintReadOnly, Category = "TurnOrder")
	TArray<ATBCPartyBase*>PartyMembers;
	UPROPERTY(BlueprintReadOnly, Category = "TurnOrder")
	TArray<ATBCEnemyBase*> EnemyCharacters;
	UFUNCTION()
	void InitHUD(UUIwithEvents* NewHUD);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnOrder")
	TArray<ABattlePosition*> SpawnPoints;
	static SpawnActors SpawnActors;
private:
	static TArray<ACharacter*> TurnOrder;
	static AActor* Camera;
	static bool bIsSomeonesTurn;
	static void ResetTurn();
	static UUIwithEvents* HUD;
	void CreateTurnOrder();
	FTimerHandle TimerHandle;
	static void TurnOrderUpdate(ACharacter* Character);
};
