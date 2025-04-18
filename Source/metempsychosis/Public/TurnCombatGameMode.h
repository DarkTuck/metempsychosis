// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	static void TurnRequest(ACharacter* Character);
	static void StartTurn();
private:
	static TArray<ACharacter*> TurnOrder;
	static bool bIsSomeonesTurn;
	static void ResetTurn();
};
