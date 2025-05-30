// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBattleControler.h"

#include "TBCEnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "TBCPartyBase.h"
#include "Elements/Columns/TypedElementAlertColumns.h"

// Sets default values for this component's properties
UAIBattleControler::UAIBattleControler(): CombatComponent(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIBattleControler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
//Temporary logic includes only attacking random target applies to both enemies and party units
void UAIBattleControler::EnemyLogic() const
{
	TArray<AActor*> Parties;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATBCPartyBase::StaticClass(),Parties);
	CombatComponent->AttackCommand(Cast<ACharacter>(Parties[FMath::RandRange(0,Parties.Num()-1)]));
}

void UAIBattleControler::PlayerLogic() const
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATBCEnemyBase::StaticClass(),Enemies);
	CombatComponent->AttackCommand(Cast<ACharacter>(Enemies[FMath::RandRange(0,Enemies.Num()-1)]));
}


// Called every frame
void UAIBattleControler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIBattleControler::HandleLogic(UTurnCombatComponent* Caller)
{
	CombatComponent=Caller;
	//UE_LOG(LogTemp, Log,TEXT("The Class is %s"),*GetOwner()->GetClass()->GetName()) ;
	Cast<ATBCBase>(GetOwner())->bIsEnemyCharacter ? EnemyLogic() : PlayerLogic();
}

