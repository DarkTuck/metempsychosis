// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ApplyDamegeNotify.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API UApplyDamegeNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void ReceiveNotify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation);
	
};
