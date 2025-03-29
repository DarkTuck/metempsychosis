// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurnCombatCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"


UCLASS()
class METEMPSYCHOSIS_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();

	void StartTurn(UTurnCombatCharacter* Character);
	void EndTurn() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UTurnCombatCharacter* CurrentCharacter;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
