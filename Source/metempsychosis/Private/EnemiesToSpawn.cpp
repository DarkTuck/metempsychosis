// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesToSpawn.h"

TArray<ATBCEnemyBase*> UEnemiesToSpawn::GetEnemies()
{
	TArray<ATBCEnemyBase*> EnemiesToReturn;
	for (TSubclassOf<ATBCEnemyBase> EnemiesClass : Enemies)
	{
		ATBCEnemyBase* CharacterToAdd = Cast<ATBCEnemyBase>(EnemiesClass);
		EnemiesToReturn.Add(CharacterToAdd);
	}
	return EnemiesToReturn;
}
