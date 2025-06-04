// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerParty.h"

TArray<ATBCPartyBase*> UPlayerParty::GetParties()
{
	TArray<ATBCPartyBase*> partiesToReturn;
	for (TSubclassOf<ATBCPartyBase>PartyCharacter : Parties)
	{
		ATBCPartyBase* PartyToReturnCharacter=Cast<ATBCPartyBase>(PartyCharacter);
		partiesToReturn.Add(PartyToReturnCharacter);
	}
	return partiesToReturn;
	
}
