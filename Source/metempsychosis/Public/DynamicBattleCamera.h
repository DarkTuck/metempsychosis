// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicBattleCamera.generated.h"

UCLASS()
class METEMPSYCHOSIS_API ADynamicBattleCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicBattleCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattleCamera")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattleCamera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattleCamera")
	class USceneComponent* Scene;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BattleCamera")
	class URotatingMovementComponent* RotatingMovement;
	FVector TargetLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetOrbit(bool bIsOrbit);
	void SetDynamicLocation(AActor* Actor,FVector Vector);
};
