// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnCombatComponent.h"
#include "Components/ActorComponent.h"
#include "AIBattleControler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class METEMPSYCHOSIS_API UAIBattleControler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBattleControler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void EnemyLogic() const;
	void PlayerLogic() const;
	UPROPERTY()
	UTurnCombatComponent* CombatComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HandleLogic(UTurnCombatComponent* Caller);

		
};
