// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnCombatComponent.h"

#include "DynamicBattleCamera.h"
#include "TurnCombatGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTurnCombatComponent::UTurnCombatComponent(): UIWidget(nullptr), Character(nullptr), BattleTransform(FTransform::Identity), Controller(nullptr)
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
	if (isPlayer)
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
void UTurnCombatComponent::EndTurn() const
{
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
    if (isPlayer)
    {
        // Upewnij się, że Controller jest poprawny
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
            
            // Spróbuj stworzyć widget z pełną weryfikacją
            UIWidget = CreateWidget<UUIwithEvents>(Controller, UIWidgetClass);
            
            if (!UIWidget)
            {
                // Jeśli się nie udało, spróbuj przez GameInstance
                if (UGameInstance* GI = GetWorld()->GetGameInstance())
                {
                    UIWidget = CreateWidget<UUIwithEvents>(GI, UIWidgetClass);
                    UE_LOG(LogTemp, Warning, TEXT("Attempting creation through GameInstance: %s"), 
                        UIWidget ? TEXT("Success") : TEXT("Failed"));
                }
            }
            
            // Jeśli widget został utworzony, ustaw timer
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
	SetCamera();
}

void UTurnCombatComponent::AddUIWidget() const
{
    if (UIWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Adding widget to viewport"));
        UIWidget->SetVisibility(ESlateVisibility::Visible);
        UIWidget->AddToViewport(100); // Wysoki Z-order dla pewności
        
        // Sprawdź czy widget jest rzeczywiście w viewport
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

void UTurnCombatComponent::SetCamera()
{
	if (ADynamicBattleCamera* Camera = Cast<ADynamicBattleCamera>(UGameplayStatics::GetActorOfClass(this, ADynamicBattleCamera::StaticClass())))
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
	BattleTransform=Character->GetActorTransform();
	
}

