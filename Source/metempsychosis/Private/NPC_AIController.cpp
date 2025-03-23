// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "NPC.h"
#include "BehaviorTree/BehaviorTree.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void ANPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc= Cast<ANPC>(InPawn))
	{
		if (UBehaviorTree* const npcBehaviorTree = npc->GetBehaviorTree())
		{
			UBlackboardComponent*b;
			UseBlackboard(npcBehaviorTree->BlackboardAsset,b);
			Blackboard=b;
			RunBehaviorTree(npcBehaviorTree);
		}
	}
}
