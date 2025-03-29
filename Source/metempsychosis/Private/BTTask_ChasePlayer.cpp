// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"


#include "NPC.h"
#include "NPC_AIController.h"
#include "TurnBaseCombat.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{
	ObjectInitializer
}
{
	NodeName = "ChasePlayer";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get target location from blackboard via the NPC's controller
	if (auto* const cont=Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		auto*const NPC = Cast<ACharacter>(cont->GetPawn());
		auto const CharMove=NPC->GetCharacterMovement();
		if (FVector::Distance(CharMove->GetLocation(),PlayerLocation)<=TriggerFightDistance)
		{
			UTurnBaseCombat::StarCombat();
		}
		//Move to player Location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont,PlayerLocation);
		//finish with success
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
