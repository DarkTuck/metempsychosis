// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombat.h"
#include "TurnManager.h"

TArray<UObject*> UTurnBaseCombat::CombatCharactersFriendly;
TArray<UObject*> UTurnBaseCombat::CombatCharactersEnemy;
int8 UTurnBaseCombat::CurrentIndex;
UTurnCombatCharacter* UTurnBaseCombat::CharactersOrder[6];
FOnStartCombat UTurnBaseCombat::StartCombatDelegate;

UTurnBaseCombat::UTurnBaseCombat()
{
}

void UTurnBaseCombat::StarCombat()
{
	StartCombatDelegate.Broadcast();
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

UTurnCombatCharacter* UTurnBaseCombat::NextCharacter(int8 currentIndex)
{
	if (currentIndex==-1)
	{
		CurrentIndex++;
	}
	else
	{
		CurrentIndex=currentIndex;
	}
	//check if index isn't higher than array lenght
	if (CurrentIndex >*(&CharactersOrder+1)-CharactersOrder)
	{
		//if is then reset index
		CurrentIndex = 0;
	}
	return CharactersOrder[CurrentIndex];
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
