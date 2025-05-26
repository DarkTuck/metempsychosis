// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplyDamegeNotify.h"
#include "TBCBase.h"

void UApplyDamegeNotify::ReceiveNotify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	const ATBCBase* Owner=Cast<ATBCBase>(MeshComp->GetOwner());
	if (const UTurnCombatComponent* CombatComp = Cast<UTurnCombatComponent>(Owner->GetComponentByClass(UTurnCombatComponent::StaticClass())); CombatComp && CombatComp->Target)
	{
		ATBCBase* Target=Cast<ATBCBase>(CombatComp->Target);
		Target->GetDamaged(Target->CalculateDamage(Owner->BaseDamage));
	}
}
