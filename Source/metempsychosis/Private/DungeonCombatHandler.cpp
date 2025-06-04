// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "DungeonCombatHandler.h"

#include "GameFramework/Character.h"
FOnStartCombat UDungeonCombatHandler::OnStartCombat;
bool UDungeonCombatHandler::bIsPlayerAdvantage;
FVector UDungeonCombatHandler::PlayerSpawnLocation;
FString UDungeonCombatHandler::MapName;
TArray<ATBCEnemyBase*> UDungeonCombatHandler::EniemiesParty;

UDungeonCombatHandler::UDungeonCombatHandler()
{
}

void UDungeonCombatHandler::StarCombat(const bool bIsPlayer, const TArray<ATBCEnemyBase*>& Party)
{
	bIsPlayerAdvantage=bIsPlayer;
	PlayerSpawnLocation = UGameplayStatics::GetPlayerCharacter(GEngine->GameViewport->GetWorld(),0)->GetActorLocation();
	EniemiesParty=Party;
	OnStartCombat.Broadcast();
}

void UDungeonCombatHandler::EndCombat(bool bPlayerWon)
{
	UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), FName(MapName));
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "BackToDungeon");
	
}
