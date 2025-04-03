// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TurnBaseCombatActor.generated.h"
UCLASS()
class METEMPSYCHOSIS_API ATurnBaseCombatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnBaseCombatActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ChangeCharacter() const;
private:
	UPROPERTY(EditAnywhere)
	ATurnManager* TurnManager;
	UPROPERTY(EditAnywhere)
	FString BattleScene;
	
	UFUNCTION()
	void StartCombat();
};
