// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)  : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = "FindRandomLocation";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	// Get AI controler and it's npc
	if (ANPC_AIController* const cont=Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc=cont->GetPawn())
		{
			//obtain  npc location to use as an orgin
			auto const Orgin = npc->GetActorLocation();

			//get the navigation system and generate random location
			if (auto* const NavSys=UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NavLoc;
				if (NavSys->GetRandomPointInNavigableRadius(Orgin,SearchRadius,NavLoc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),NavLoc.Location);
				}
				//finish with success
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
