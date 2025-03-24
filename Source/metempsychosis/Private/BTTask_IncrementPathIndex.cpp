// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"

#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = "IncrementPathIndex";
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//try and get AI controller
	if (auto*const Cont=Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		//try and get NPC
		if (auto* const NPC = Cast<ANPC>(Cont->GetPawn()))
		{
			//try and get blackboard
			if (auto* const BC = OwnerComp.GetBlackboardComponent())
			{
				//get number of path points and min max indices
				auto const NoOfPoints = NPC->GetPatrolPath()->NUM();
				constexpr auto MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				//change direction if we ate at the first or last index if we are in bidirectional mode
				if (bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction=EDirectionType::Reverse;
					}
					else if (Index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction=EDirectionType::Forward;
					}
				}

				// set new value of index to blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(), (Direction== EDirectionType::Forward ?++Index:--Index) %NoOfPoints);

				//finish with succes
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
