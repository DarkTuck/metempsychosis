// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePosition.h"
#include "Components/SceneComponent.h"

// Sets default values
ABattlePosition::ABattlePosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Arrow=CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(0,0,40));

}

void ABattlePosition::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (isEnemy)
	{
		Arrow->SetArrowColor(FLinearColor::Red);
	}
	else
	{
		Arrow->SetArrowColor(FLinearColor::Green);
	}
}

void ABattlePosition::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnCharacter();
}

void ABattlePosition::SpawnCharacter()
{
	if (Character!=nullptr)
	{
		if (UWorld* const World=GetWorld())
		{
			FVector const SpawnLocation=GetActorLocation();
			FRotator const SpawnRotation=GetActorRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			AActor* SpawnedCActor = World->SpawnActor<AActor>(Character,SpawnLocation,SpawnRotation,SpawnParams);
		}
	}
}

// Called every frame
void ABattlePosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

