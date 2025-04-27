// Fill out your copyright notice in the Description page of Project Settings.


#include "TBCPlayerController.h"

#include "Blueprint/UserWidget.h"

ATBCPlayerController::ATBCPlayerController()
{
	APlayerController::AutoManageActiveCameraTarget(nullptr);
	bShowMouseCursor = true;
	
}


void ATBCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess wywołane"));
}



void ATBCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*
	UIWidget = CreateWidget<UUIwithEvents>(this,UIWidgetClass);
	if (UIWidget)
	{
		UIWidget->AddToViewport();
		OnHUDCreated.Broadcast(UIWidget);
	}
	*/
	if (!UIWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("UIWidgetClass jest NULL!"));
		return;
	}
    
	UE_LOG(LogTemp, Warning, TEXT("UIWidgetClass jest ustawiony: %s"), *UIWidgetClass->GetName());
    
	UIWidget = CreateWidget<UUIwithEvents>(this, UIWidgetClass);
	if (!UIWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateWidget zwrócił NULL!"));
		return;
	}
    
	UE_LOG(LogTemp, Warning, TEXT("Widget został stworzony"));
	UIWidget->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("Próba wywołania OnHUDCreated"));
	OnHUDCreated.Broadcast(UIWidget);
	UE_LOG(LogTemp, Warning, TEXT("OnHUDCreated wywołane"));
}
