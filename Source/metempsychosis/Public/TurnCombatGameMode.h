// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIwithEvents.h"
#include "GameFramework/GameModeBase.h"
#include "TurnCombatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API ATurnCombatGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATurnCombatGameMode();
	static void TurnRequest(ACharacter* Character);
	static void StartTurn();
	virtual void BeginPlay() override;
	UFUNCTION()
	void InitHUD(UUIwithEvents* NewHUD);
private:
	static TArray<ACharacter*> TurnOrder;
	static AActor* Camera;
	TArray<AActor*>PartyMembers,EnemyCharacters;
	static bool bIsSomeonesTurn;
	static void ResetTurn();
	static UUIwithEvents* HUD;
	void CreateTurnOrder();
	static void TurnOrderUpdate(ACharacter* Character);
};
