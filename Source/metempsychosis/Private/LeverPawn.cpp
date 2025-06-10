// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverPawn.h"

#include "EnhancedInputComponent.h"

// Sets default values
ALeverPawn::ALeverPawn(): InteractAction(nullptr), Target(nullptr)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALeverPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALeverPawn::Interact(const FInputActionInstance& Instance)
{
	if (bCouldInteract)
	{
		SetActorRotation(FMath::Lerp(GetActorRotation(), FRotator(0, 0, 0), 0.1f));
	}
}

// Called every frame
void ALeverPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALeverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALeverPawn::Interact);

}

