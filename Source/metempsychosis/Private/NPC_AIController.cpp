// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "NPC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "metempsychosis/metempsychosisCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
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

void ANPC_AIController::SetupPerceptionSystem()
{
	SightConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));
		SightConfig->SightRadius=500.f;
		SightConfig->LoseSightRadius=SightConfig->SightRadius+25.f;
		SightConfig->PeripheralVisionAngleDegrees=90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation=520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies=true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies=true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals=true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,&ANPC_AIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ANPC_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto const character = Cast<AmetempsychosisCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer",Stimulus.WasSuccessfullySensed());
	}
}
