// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCPlayerController.h"
#include "Components/ActorComponent.h"
#include "TurnCombatComponent.generated.h"

class UUIwithEvents;

DECLARE_DELEGATE(EndTurnDelegate);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METEMPSYCHOSIS_API UTurnCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurnCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void BeginTurn();
	void EndTurn() const;
	void AddUIWidget() const;
	FTimerHandle TimerHandle;
	EndTurnDelegate EndTurnDelegate;
	
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	//int Health=100;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	//int AttackPower=20;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	//int ActionPoints=3;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="TurnBaseCombatCharacter")
	//bool bIsFriendly=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	int Strength;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	int Accuracy;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	int Haste;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	int Stamina;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	int Wisdom;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	bool isPlayer=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> UIWidgetClass;
	
protected:
	UPROPERTY()
	UUIwithEvents* UIWidget;
	UPROPERTY()
	ACharacter* Character;
	FTransform BattleTransform;
	UPROPERTY()
	ATBCPlayerController* Controller;
	void SetCamera();
	//int GetActionPoints() const { return ActionPoints; }

	void RequestTurn() const;

	void SpendActionPoints(int Amount);

	void BeginCombat();


		
};
