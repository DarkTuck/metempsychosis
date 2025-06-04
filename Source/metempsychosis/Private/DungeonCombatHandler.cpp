// Fill out your copyright notice in the Description page of Project Settings.
#include "DungeonCombatHandler.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "metempsychosis/metempsychosisCharacter.h"


FOnStartCombat UDungeonCombatHandler::OnStartCombat;
bool UDungeonCombatHandler::bIsPlayerAdvantage;
FVector UDungeonCombatHandler::PlayerSpawnLocation;
FString UDungeonCombatHandler::MapName;
TArray<ATBCEnemyBase*> UDungeonCombatHandler::EniemiesParty;
TArray<ATBCPartyBase*> UDungeonCombatHandler::Parties;

UDungeonCombatHandler::UDungeonCombatHandler()
{
}

void UDungeonCombatHandler::StarCombat(const bool bIsPlayer, const TArray<ATBCEnemyBase*>& Party)
{
	bIsPlayerAdvantage=bIsPlayer;
	const UObject* WorldContext=GEngine->GameViewport->GetWorld();
	PlayerSpawnLocation = UGameplayStatics::GetPlayerCharacter(WorldContext,0)->GetActorLocation();
	EniemiesParty=Party;
	Parties=Cast<AmetempsychosisCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContext,0))->GetParties();
	OnStartCombat.Broadcast();
}

void UDungeonCombatHandler::EndCombat(bool bPlayerWon)
{
	UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), FName(MapName));
	return GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, "BackToDungeon");
	
}
