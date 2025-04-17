// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombat.h"
#include "TurnManager.h"

TArray<UObject*> UTurnBaseCombat::CombatCharactersFriendly;
TArray<UObject*> UTurnBaseCombat::CombatCharactersEnemy;
int8 UTurnBaseCombat::CurrentIndex;
UTurnCombatCharacter* UTurnBaseCombat::CharactersOrder[6];
FOnStartCombat UTurnBaseCombat::StartCombatDelegate;
bool UTurnBaseCombat::bPlayerAdvantage;

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
	const int8 friendlyCount = CombatCharactersFriendly.Num();
	const int8 enemyCount = CombatCharactersEnemy.Num();
	const int8 totalCharacters = friendlyCount + enemyCount;
    
	// Check character limit and if not over it
	if (totalCharacters > MAX_CHARACTERS)
	{
		return;
	}
    
	// Reset Order
	for (int8 i = 0; i < MAX_CHARACTERS; i++)
	{
		CharactersOrder[i] = nullptr;
	}
    
	int8 currentIndex = 0;
    
	if (bPlayerAdvantage)
	{
		// Add Friendly characters
		for (int8 i = 0; i < friendlyCount; i++)
		{
			if (CombatCharactersFriendly[i] != nullptr)
			{
				CharactersOrder[currentIndex] = Cast<UTurnCombatCharacter>(CombatCharactersFriendly[i]);
				currentIndex++;
			}
		}
        
		// Add Enemies
		for (int8 i = 0; i < enemyCount; i++)
		{
			if (CombatCharactersEnemy[i] != nullptr)
			{
				CharactersOrder[currentIndex] = Cast<UTurnCombatCharacter>(CombatCharactersEnemy[i]);
				currentIndex++;
			}
		}
	}
	else
	{
		// Add Enemies
		for (int8 i = 0; i < enemyCount; i++)
		{
			if (CombatCharactersEnemy[i] != nullptr)
			{
				CharactersOrder[currentIndex] = Cast<UTurnCombatCharacter>(CombatCharactersEnemy[i]);
				currentIndex++;
			}
		}
        
		// Add friendly
		for (int8 i = 0; i < friendlyCount; i++)
		{
			if (CombatCharactersFriendly[i] != nullptr)
			{
				CharactersOrder[currentIndex] = Cast<UTurnCombatCharacter>(CombatCharactersFriendly[i]);
				currentIndex++;
			}
		}
	}
}

void UTurnBaseCombat::EndCombat()
{
	return GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "End Fight");
}
