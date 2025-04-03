// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurnCombatCharacter.h"
#include "CoreMinimal.h"
#include "TurnBaseCombat.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartCombat);
UCLASS()
class METEMPSYCHOSIS_API UTurnBaseCombat : public UObject
{
	GENERATED_BODY()
public:
	UTurnBaseCombat();
	static void StarCombat();
	static void CharacterDies(UObject* Character,bool bIsFriendly);
	static void AddCharacter(UObject* Character,bool bIsFriendly);
	static UTurnCombatCharacter* NextCharacter(int8 currentIndex=-1);
	static void OrderCharacter();
	static  FOnStartCombat StartCombatDelegate;
private:

	static void EndCombat();
	static UTurnCombatCharacter* CharactersOrder[6];
	static TArray<UObject*> CombatCharactersFriendly;
	static TArray<UObject*> CombatCharactersEnemy;
	static int8 CurrentIndex;

};
