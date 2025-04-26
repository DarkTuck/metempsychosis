// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicBattleCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADynamicBattleCamera::ADynamicBattleCamera() : TargetLocation(0,0,0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(Scene);
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Scene);
	SpringArm->SetRelativeLocation(FVector(0,0,0));
	SpringArm->SetRelativeRotation(FRotator(-50,0,0));
	SpringArm->TargetArmLength = 250;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritYaw = false;
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->SetUpdatedComponent(Scene);
	

}

// Called when the game starts or when spawned
void ADynamicBattleCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADynamicBattleCamera::SetOrbit(bool bIsOrbit)
{
	RotatingMovement->RotationRate = FRotator(0,bIsOrbit?10:0,0);
	SpringArm->bInheritYaw = bIsOrbit;
	if (!bIsOrbit)
	{
		SetActorRotation(FRotator(0,0,0));
	}
}

void ADynamicBattleCamera::SetDynamicLocation(AActor* Actor, const FVector& Vector)
{
	if (Actor)
	{
		AttachToActor(Actor,FAttachmentTransformRules::KeepRelativeTransform);
		Camera->SetRelativeLocation(FVector(0,0,0));
	}
	else
	{
		TargetLocation = Vector;
	}
}

// Called every frame
void ADynamicBattleCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetAttachParentActor())
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(),TargetLocation,DeltaTime,5));
	}

}

