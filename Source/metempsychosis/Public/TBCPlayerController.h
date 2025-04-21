// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIwithEvents.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "TBCPlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDCreated, UUIwithEvents*, CreatedHUD);
UCLASS()
class METEMPSYCHOSIS_API ATBCPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATBCPlayerController();
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UUIwithEvents* UIWidget;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	UPROPERTY()
	FOnHUDCreated OnHUDCreated;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> UIWidgetClass;
};
