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
	void CharacterDies(bool bIsParty,ACharacter* Character);
	UPROPERTY(BlueprintReadOnly, Category = "TurnOrder")
	TArray<AActor*>PartyMembers;
	UPROPERTY(BlueprintReadOnly, Category = "TurnOrder")
	TArray<AActor*> EnemyCharacters;
	UFUNCTION()
	void InitHUD(UUIwithEvents* NewHUD);
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
