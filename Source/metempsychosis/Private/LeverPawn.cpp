// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverPawn.h"
#include "Kismet/GameplayStatics.h"
#include "metempsychosis/metempsychosisCharacter.h"

// Sets default values
ALeverPawn::ALeverPawn(): selfRotation(0, 0, 0), TargetYMultiplayer(0), Alpha(0), LeverMesh(nullptr)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALeverPawn::BeginPlay()
{
	Super::BeginPlay();
	Cast<AmetempsychosisCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->InteractionDelegate.AddUObject(this, &ALeverPawn::Interact);	
}

void ALeverPawn::Interact() const
{
	UE_LOG(LogTemp, Log, TEXT("Interact"));
	if (bCouldInteract)
	{
		//SetActorRotation(FMath::Lerp(GetActorRotation(), selfRotation, Alpha));
		//LeverMesh->SetRelativeRotation(FMath::Lerp(LeverMesh->GetRelativeRotation(), selfRotation, Alpha));
		LeverMesh->SetRelativeRotation(selfRotation);
		//const FVector TargetLocation = Target->GetActorLocation();
		//Target->SetActorLocation(FMath::Lerp(TargetLocation,TargetLocation+FVector(0,TargetYMultiplayer,0) , Alpha));
		//Target->SetActorLocation(TargetLocation+FVector(TargetYMultiplayer,0,0));
		for (AActor* Actor : Target)
		{
			const FVector TargetLocation = Actor->GetActorLocation();
			Actor->SetActorLocation(TargetLocation+FVector(TargetYMultiplayer,0,0));
		}
	}
}

// Called every frame
void ALeverPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

void ALeverPawn::SetbCouldInteract(const bool bSet)
{
	bCouldInteract = bSet;
}

