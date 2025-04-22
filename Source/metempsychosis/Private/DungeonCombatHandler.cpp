// Fill out your copyright notice in the Description page of Project Settings.



#include "DungeonCombatHandler.h"
FOnStartCombat UDungeonCombatHandler::OnStartCombat;
bool UDungeonCombatHandler::bIsPlayerAdvantage;

UDungeonCombatHandler::UDungeonCombatHandler()
{
}

void UDungeonCombatHandler::StarCombat(bool bIsPlayer)
{
	bIsPlayerAdvantage=bIsPlayer;
	OnStartCombat.Broadcast();
}
