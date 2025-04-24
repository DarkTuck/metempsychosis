// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "BattlePosition.generated.h"

UCLASS()
class METEMPSYCHOSIS_API ABattlePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattlePosition();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattlePosition",meta=(AllowPrivateAccess=true))
	UClass* Character;
	UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattlePosition",meta=(AllowPrivateAccess=true))
	bool isEnemy;
	void SpawnCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
