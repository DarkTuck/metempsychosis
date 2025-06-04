// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"


#include "NPC.h"
#include "NPC_AIController.h"
#include "DungeonCombatHandler.h"
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
	// get target location from the blackboard via the NPC's controller
	if (auto* const Cont=Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		const auto*const NPC = Cast<ACharacter>(Cont->GetPawn());
		if (auto const CharMove=NPC->GetCharacterMovement(); FVector::Distance(CharMove->GetLocation(),PlayerLocation)<=TriggerFightDistance)
		{
			const auto Anpc=Cast<ANPC>(Cont->GetPawn());
		UDungeonCombatHandler::StarCombat(false,Anpc->GetEnemiesToSpawn());
			Anpc->Destroy();
		}
		//Move to player Location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Cont,PlayerLocation);
		//finish with success
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
