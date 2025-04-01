// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombat.h"

#include "TurnManager.h"

TArray<UObject*> UTurnBaseCombat::CombatCharactersFriendly;
TArray<UObject*> UTurnBaseCombat::CombatCharactersEnemy;
int8 UTurnBaseCombat::CurrentIndex;
UTurnCombatCharacter* UTurnBaseCombat::CharactersOrder[6];

UTurnBaseCombat::UTurnBaseCombat()
{
	
}

void UTurnBaseCombat::StarCombat()
{
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "Trigger Fight");
}

void UTurnBaseCombat::CharacterDies(UObject* Character, const bool bIsFriendly)
{
	if (bIsFriendly)
	{
		if (CombatCharactersFriendly.Num()<=0)
		{
			EndCombat();
			return;
		}
		return;
	}
	CombatCharactersEnemy.Remove(Character);
	if (CombatCharactersEnemy.Num()<=0)
	{
		EndCombat();
	}
}

void UTurnBaseCombat::AddCharacter(UObject* Character, const bool bIsFriendly)
{
	if (bIsFriendly)
	{
		CombatCharactersFriendly.Add(Character);
		return;
	}
	CombatCharactersEnemy.Add(Character);
}

void UTurnBaseCombat::NextCharacter(int8 currentIndex)
{
	currentIndex++;
	CurrentIndex=currentIndex;
	//ATurnManager->StartTurn(CharactersOrder[currentIndex]);
}

void UTurnBaseCombat::OrderCharacter()
{
	for (int8 i=0;i<=6;i++)
	{
		if (i<=3)
		{
			if (CombatCharactersFriendly[i]!=nullptr)
			{
				CharactersOrder[i]=Cast<UTurnCombatCharacter>(CombatCharactersFriendly[i]);
				return;
			}
			return;
		}
		if (CombatCharactersEnemy[i]!=nullptr)
		{
			CharactersOrder[i]=Cast<UTurnCombatCharacter>(CombatCharactersEnemy[i]);
		}
	}
}

void UTurnBaseCombat::EndCombat()
{
	return GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "End Fight");
}
