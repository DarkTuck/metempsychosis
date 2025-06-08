// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatComponent.h"

#include "AIBattleControler.h"
#include "AIController.h"
#include "DynamicBattleCamera.h"
#include "TBCBase.h"
#include "TopDownCamera.h"
#include "TurnCombatGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values for this component's properties
UTurnCombatComponent::UTurnCombatComponent(): Target(nullptr), BattleTransform(FTransform::Identity), HitAnimMontage(nullptr),
                                              UIWidget(nullptr), Character(nullptr),
                                              Controller(nullptr),
                                              Camera(nullptr),
                                              bIsRangedCharacter(false),
                                              AIController(nullptr), TopDownCamera(nullptr),
                                              TemporaryCameraPawn(nullptr),
                                              OriginalController(nullptr)
{
	// Set this component to be initialized when the game starts and to be ticked every frame.
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTurnCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	TopDownCamera=UGameplayStatics::GetActorOfClass(this, ATopDownCamera::StaticClass());
	if (Cast<ATBCBase>(GetOwner())->bIsPlayer)
	{
		Controller=Cast<ATBCPlayerController>(GetWorld()->GetFirstPlayerController());
		if (Controller)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller is not NULL"));
		}
	}
}


// Called every frame
void UTurnCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
/*
void UTurnCombatComponent::BeginTurn()
{
	if (isPlayer)
	{
		if (UIWidgetClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("UIWidgetClass is not NULL"));
		}
		UIWidget = CreateWidget<UUIwithEvents>(Controller,UIWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("Created Widget: %s"), UIWidget ? TEXT("Success") : TEXT("Failed"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTurnCombatComponent::AddUIWidget, 0.0001f,false);

	}
	//Reset or refill action points at the beginning of the turn
	//ActionPoints = 3;
}
*/
void UTurnCombatComponent::EndTurn()
{
	RestoreOriginalController();
	EndTurnDelegate.ExecuteIfBound();
}

/*
void UTurnCombatComponent::AddUIWidget() const
{
	if (UIWidget)
	{
		UIWidget->AddToViewport();
	}
}
*/
void UTurnCombatComponent::BeginTurn()
{
    if (Cast<ATBCBase>(GetOwner())->bIsPlayer)
    {
        if (!Controller)
        {
            Controller = Cast<ATBCPlayerController>(GetWorld()->GetFirstPlayerController());
            UE_LOG(LogTemp, Warning, TEXT("Attempting to get controller again: %s"), 
                Controller ? TEXT("Success") : TEXT("Failed"));
        }

        if (Controller && UIWidgetClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("Attempting to create widget..."));
            UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *Controller->GetName());
            UE_LOG(LogTemp, Warning, TEXT("UIWidgetClass: %s"), *UIWidgetClass->GetName());

            UIWidget = CreateWidget<UUIwithEvents>(Controller, UIWidgetClass);
        	UIWidget->SetPlayerCharacter(Cast<ATBCBase>(Character));
            if (!UIWidget)
            {
                if (UGameInstance* GI = GetWorld()->GetGameInstance())
                {
                    UIWidget = CreateWidget<UUIwithEvents>(GI, UIWidgetClass);
                    UE_LOG(LogTemp, Warning, TEXT("Attempting creation through GameInstance: %s"), 
                        UIWidget ? TEXT("Success") : TEXT("Failed"));
                }
            }
        	
            if (UIWidget)
            {
                GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTurnCombatComponent::AddUIWidget, 0.1f, false);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create widget after all attempts"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Missing requirements - Controller: %s, UIWidgetClass: %s"), 
                Controller ? TEXT("Valid") : TEXT("NULL"),
                UIWidgetClass ? TEXT("Valid") : TEXT("NULL"));
        }
    }
	else
	{
		if (UAIBattleControler* Controler = Cast<UAIBattleControler>(GetOwner()->GetComponentByClass(UAIBattleControler::StaticClass())))
        {
        	Controler->HandleLogic(this);
        }
	}
	SetCamera();

}

void UTurnCombatComponent::AddUIWidget() const
{
    if (UIWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Adding widget to viewport"));
        UIWidget->SetVisibility(ESlateVisibility::Visible);
        UIWidget->AddToViewport(100); // High Z-order for safety reasons
    	
        if (UIWidget->IsInViewport())
        {
            UE_LOG(LogTemp, Warning, TEXT("Widget successfully added to viewport"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Widget failed to add to viewport"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Widget is NULL in AddUIWidget"));
    }
}

void UTurnCombatComponent::AttackCommand(ACharacter* AttackTarget)
{
	Target=AttackTarget;
	//Camera->SetOrbit(IsValid(Controller->GetViewTarget()));
	if (bIsRangedCharacter)
	{
		RangeAttack();
	}
	else
	{
		CloseAttack();
	}
}
void UTurnCombatComponent::CloseAttack()
{
	if (UIWidget)
	{
		UIWidget->RemoveFromParent();
	}

	if (!AIController)
	{
		SwitchToAIController();
	}
	if (const EPathFollowingRequestResult::Type Result = AIController->MoveToActor(Target, true); Result == EPathFollowingRequestResult::RequestSuccessful)
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this, &UTurnCombatComponent::OnMoveToTargetCompleted);
	}
	else if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		OnMoveToTargetCompleted(FAIRequestID::InvalidRequest, EPathFollowingResult::Success);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CloseAttack: Moving Error: %s"), 
			Result == EPathFollowingRequestResult::Failed ? TEXT("FailedToFindPath") : TEXT("UnknownError"));
	}


}

void UTurnCombatComponent::RangeAttack()
{
	if (UIWidget)
	{
		UIWidget->RemoveFromParent();
	}

	if (!AIController)
	{
		SwitchToAIController();
	}
	PerformAttack();
}

void UTurnCombatComponent::OnMoveToTargetCompleted(FAIRequestID RequestID, const EPathFollowingResult::Type Result)
{
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.RemoveDynamic(this,&UTurnCombatComponent::OnMoveToTargetCompleted);
	}
	if (Result==EPathFollowingResult::Success)
	{
		PerformAttack();
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Move Failed:%d"),static_cast<int>(Result));
	}
}

void UTurnCombatComponent::PerformAttack()
{
	//Temporary
	ATBCBase* TargetCharacter=Cast<ATBCBase>(Target);
	UE_LOG(LogTemp,Log,TEXT("Damage: %d"),TargetCharacter->CalculateDamage(Cast<ATBCBase>(GetOwner())->BaseDamage));
	TargetCharacter->GetDamaged(TargetCharacter->CalculateDamage(Cast<ATBCBase>(GetOwner())->BaseDamage));
	if (const EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(BattleTransform.GetLocation(), true); Result == EPathFollowingRequestResult::RequestSuccessful)
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this, &UTurnCombatComponent::OnMoveToLocationCompleted);
	}
	else if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		OnMoveToLocationCompleted(FAIRequestID::InvalidRequest, EPathFollowingResult::Success);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PerformAttack: Moving Error: %s"), 
			Result == EPathFollowingRequestResult::Failed ? TEXT("FailedToFindPath") : TEXT("UnknownError"));
	}
}

void UTurnCombatComponent::OnMoveToLocationCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UTurnCombatComponent::OnMoveToLocationCompleted);
	}

	Character->SetActorRotation(BattleTransform.GetRotation());
	FTimerHandle DelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DelayTimerHandle,
		[this]
		{
			EndTurn();
		},2.0f,false);
	
}

void UTurnCombatComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	Character=Cast<ACharacter>(GetOwner());
}
void UTurnCombatComponent::SwitchToAIController()
{
	 // Early return if Character reference is invalid
    if (!Character)
    {
        UE_LOG(LogTemp, Error, TEXT("SwitchToAIController: Character is NULL"));
        return;
    }
    
    // Get the current controller and check if it's already an AIController
    AController* CurrentController = Character->GetController();
    if (CurrentController && CurrentController->IsA(AAIController::StaticClass()))
    {
        // If a character is already controlled by AIController, store the reference
        AIController = Cast<AAIController>(CurrentController);
        UE_LOG(LogTemp, Warning, TEXT("Character is already possessed by AIController"));
        return;
    }
    
    // Store the original controller if not already stored
    if (!OriginalController)
    {
        OriginalController = CurrentController;
        UE_LOG(LogTemp, Warning, TEXT("Stored original controller: %s"), 
            OriginalController ? *OriginalController->GetClass()->GetName() : TEXT("NULL"));
    }

    // Unpossess current controller if it exists
    if (CurrentController)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unpossessing current controller: %s"), 
            *CurrentController->GetClass()->GetName());
        CurrentController->UnPossess();
    }
    
    // Setup spawn parameters for new AIController
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = nullptr; // Important: Don't set an owner to avoid owner loop
    SpawnParams.Instigator = Character;
    
    // Spawn new AIController
    AIController = GetWorld()->SpawnActor<AAIController>(
        AAIController::StaticClass(), 
        FVector::ZeroVector, 
        FRotator::ZeroRotator, 
        SpawnParams
    );
	TemporaryCameraPawn = GetWorld()->SpawnActor<APawn>(APawn::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    
    // Possess the character with a new AIController if spawn was successful
    if (AIController)
    {
        AIController->Possess(Character);
    	Controller->Possess(TemporaryCameraPawn);
    	Controller->SetViewTarget(Character);
    	//Camera->SetDynamicLocation(Character,FVector(0,0,0));
        UE_LOG(LogTemp, Warning, TEXT("Successfully switched character %s to AIController"), 
            *Character->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create AIController"));
    }
}

void UTurnCombatComponent::RestoreOriginalController()
{
	if (!Character || !OriginalController) return;
    
	// Unposses AIController
	if (AIController)
	{
		AIController->UnPossess();
		AIController->Destroy();
		TemporaryCameraPawn->Destroy();
		Controller->UnPossess();
		AIController = nullptr;
	}
    
	// return to normal controller
	OriginalController->Possess(Character);
	Controller->SetViewTarget(Camera);
	UE_LOG(LogTemp, Warning, TEXT("Restored Controller for: %s"), *Character->GetName());
}


void UTurnCombatComponent::SetCamera()
{
	Camera = Cast<ADynamicBattleCamera>(UGameplayStatics::GetActorOfClass(this, ADynamicBattleCamera::StaticClass()));
	if (Camera)
	{
		if (!Controller)
		{
			Controller = Cast<ATBCPlayerController>(GetWorld()->GetFirstPlayerController());
		}
		if (Controller)
		{
			Controller->SetViewTarget(Camera);
			Camera->SetDynamicLocation(Character,FVector(0,0,0));
			Camera->SetOrbit(Controller->GetViewTarget()!=nullptr);
		}

	}
}

/*
void UTurnCombatComponent::TakeDamage(const int DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		UTurnBaseCombat::AddCharacter(this,bIsFriendly);
	}
}


void UTurnCombatComponent::Attack(UTurnCombatComponent* Target)
{
	//if (ActionPoints > 0)
	//{
		//Target->TakeDamage(AttackPower);
		//SpendActionPoints(1);
	//}
}
*/
void UTurnCombatComponent::RequestTurn() const
{
	ATurnCombatGameMode::TurnRequest(Character);
}

void UTurnCombatComponent::SpendActionPoints(const int Amount)
{
	//ActionPoints -= Amount;
}

void UTurnCombatComponent::BeginCombat()
{
	Character=Cast<ACharacter>(GetOwner());
	//BattleTransform=Character->GetActorTransform();
	if (AController* CurrentController = Character->GetController())
	{
		UE_LOG(LogTemp, Warning, TEXT("BeginCombat - Controller class: %s"), *CurrentController->GetClass()->GetName());
		OriginalController=CurrentController;
	}
    

	AIController = Cast<AAIController>(Character->GetController());
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not found for character %s"), *Character->GetName());
	}

	
}