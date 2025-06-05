// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerParty.h"

TArray<ATBCPartyBase*> UPlayerParty::GetParties()
{
	TArray<ATBCPartyBase*> ReturnArray;
	for (int8 i = 0; i < Parties.Num(); i++)
	{
		const UClass* Character = Parties[i].LoadSynchronous();
		ATBCPartyBase* Party = Character->GetDefaultObject<ATBCPartyBase>();
		ReturnArray.Add(Party);
		UE_LOG(LogTemp,Log,TEXT("Added Character:%s"),*Party->GetName());
	}
	return ReturnArray;
	

}
