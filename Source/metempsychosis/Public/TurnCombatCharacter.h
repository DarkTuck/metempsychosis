// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnCombatCharacter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METEMPSYCHOSIS_API UTurnCombatCharacter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurnCombatCharacter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void BeginTurn();
	void EndTurn();

	void TakeDamage(int DamageAmount);
	void Attack(UTurnCombatCharacter* Target);

protected:
	int GetActionPoints() const { return ActionPoints; }
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	int Health=100;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	int AttackPower=20;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	int ActionPoints=3;

	void SpendActionPoints(int Amount);

		
};
