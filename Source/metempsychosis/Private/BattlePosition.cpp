// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePosition.h"

#include "TBCBase.h"
#include "TurnCombatGameMode.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattlePosition::ABattlePosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Arrow=CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(0,0,40));

}

void ABattlePosition::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (bIsEnemy)
	{
		Arrow->SetArrowColor(FLinearColor::Red);
	}
	else
	{
		Arrow->SetArrowColor(FLinearColor::Green);
	}
}

void ABattlePosition::BeginPlay()
{
	Super::BeginPlay();
	ATurnCombatGameMode::SpawnActors.AddUObject(this,&ABattlePosition::SpawnCharacter);
}

void ABattlePosition::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Cast<ATurnCombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnActors.AddUObject(this,&ABattlePosition::SpawnCharacter);
	//SpawnCharacter();
}

void ABattlePosition::SpawnCharacter()
{
	if (Character!=nullptr)
	{
			FVector const SpawnLocation=GetActorLocation();
			FRotator const SpawnRotation=GetActorRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			UWorld* const World = GetWorld();
			AActor* const SpawnedCActor = World->SpawnActor<AActor>(Character,SpawnLocation,SpawnRotation,SpawnParams);
			Cast<ATBCBase>(SpawnedCActor)->GetComponentByClass<UTurnCombatComponent>()->BattleTransform=GetActorTransform();
			Cast<ATurnCombatGameMode>(UGameplayStatics::GetGameMode(World))->RegisterCharacter(Cast<ATBCBase>(SpawnedCActor),bIsEnemy);
	}
}

// Called every frame
void ABattlePosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

