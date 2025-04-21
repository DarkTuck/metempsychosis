// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBCBase.h"
#include "Blueprint/UserWidget.h"
#include "UIwithEvents.generated.h"

/**
 * 
 */
UCLASS()
class METEMPSYCHOSIS_API UUIwithEvents : public UUserWidget
{
	GENERATED_BODY()
public:
	UUIwithEvents(const FObjectInitializer& ObjectInitializer);

	// Deklaracja funkcji, którą zaimplementujesz w Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateHealthBar(float NewHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void AddCharacter(ATBCBase* character);

	// Opcjonalnie - funkcja z domyślną implementacją w C++
	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void ShowGameOverScreen(const FString& Message);
};

