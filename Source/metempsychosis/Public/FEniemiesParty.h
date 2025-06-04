#pragma once
#include "CoreMinimal.h"
#include "TBCEnemyBase.h"
#include "FEniemiesParty.generated.h"

USTRUCT(BlueprintType)
struct FEniemiesParty
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<ATBCEnemyBase*> Enemies;
};
