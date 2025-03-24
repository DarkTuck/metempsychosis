// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"

#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)  : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = "FindPathPoint";
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont=Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		//attempt to get the blackboard component from the behavior tree
		if (auto* const bc=OwnerComp.GetBlackboardComponent())
		{
			//get the current patrol path index from the blackboard
			auto const Index = bc->GetValueAsInt(GetSelectedBlackboardKey());

			//get the NPC
			if (auto* npc = Cast<ANPC>(cont->GetPawn()))
			{
				//get the current patrol path vector from the NPC - this is local to patrol path actor
				auto const Point=npc->GetPatrolPath()->GetPathPoint(Index);

				//convert local to global vector
				auto const GlobalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PathPointVectorKey.SelectedKeyName, GlobalPoint);

				//finish with success
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
