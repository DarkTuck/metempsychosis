// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnCombatComponent.h"
#include "GameFramework/Character.h"
#include "TBCBase.generated.h"
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRefreshUI);
UCLASS()
class METEMPSYCHOSIS_API ATBCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATBCBase();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterStats")
	bool bIsPlayer=false;
	UPROPERTY()
	bool bIsEnemyCharacter=false;
	int CalculateDamage(int Damage) const;
	UPROPERTY(BlueprintReadWrite,Category="TBCBatlleStats",EditAnywhere)
	int BaseDamage;
	void GetDamaged(int Damage);
	UPROPERTY(BlueprintAssignable,Category="TBC")
	FRefreshUI RefreshUI;
protected:
	UPROPERTY(BlueprintReadWrite,Category="TBCName",EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite,Category="TBCBatlleStats",EditAnywhere)
	int HP;
	UPROPERTY(BlueprintReadWrite,Category="TBCStats",EditAnywhere)
	int MaxHP;
	UPROPERTY(BlueprintReadWrite,Category="TBCBatlleStats",EditAnywhere)
	int DamageReduction;
	UPROPERTY(BlueprintReadWrite,Category="TBCBatlleStats",EditAnywhere)
	int MP;
	UPROPERTY(BlueprintReadWrite,Category="TBCStats",EditAnywhere)
	int MaxMP;

	UPROPERTY(BlueprintReadWrite,Category="TBC",EditAnywhere)
	UTurnCombatComponent* CombatComponent;
	UFUNCTION(BlueprintCallable,Category="TBC")
	void SendAttackCommand(ACharacter* Target);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
