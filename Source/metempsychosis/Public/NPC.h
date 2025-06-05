// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemiesToSpawn.h"
#include "PatrolPath.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class METEMPSYCHOSIS_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();
	//UPROPERTY()
	//UEnemiesToSpawn* Party;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UEnemiesToSpawn> PartySubclass;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	UEnemiesToSpawn* CachedPartyAsset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	APatrolPath* PatrolPath;
	void LoadPartyAsset();
	void OnPartyAssetLoaded();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UBehaviorTree* GetBehaviorTree() const;
	APatrolPath* GetPatrolPath() const;
	TArray<ATBCEnemyBase*> GetEnemiesToSpawn() const;

};
