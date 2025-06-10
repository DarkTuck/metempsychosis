// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "LeverPawn.generated.h"

UCLASS()
class METEMPSYCHOSIS_API ALeverPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALeverPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Interact(const FInputActionInstance& Instance);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	AActor* Target;
	UPROPERTY()
	bool bCouldInteract=false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
