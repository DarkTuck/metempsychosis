// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesToSpawn.h"

void UEnemiesToSpawn::RequestAsyncLoad(const UObject* DataOwner)
{
}

void UEnemiesToSpawn::RequestAsyncUnload(const UObject* DataOwner)
{
}

TArray<ATBCEnemyBase*> UEnemiesToSpawn::GetEnemies() const
{
	TArray<ATBCEnemyBase*> ReturnArray;
	for (int8 i = 0; i < Enemies.Num(); i++)
	{
		const UClass* Character = Enemies[i].LoadSynchronous();
		ATBCEnemyBase* Enemy = Character->GetDefaultObject<ATBCEnemyBase>();
		ReturnArray.Add(Enemy);
		UE_LOG(LogTemp,Log,TEXT("Added Character:%s"),*Enemy->GetName());
	}
	return ReturnArray;
}
