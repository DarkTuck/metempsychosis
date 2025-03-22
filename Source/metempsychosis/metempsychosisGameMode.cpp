// Copyright Epic Games, Inc. All Rights Reserved.

#include "metempsychosisGameMode.h"
#include "metempsychosisCharacter.h"
#include "UObject/ConstructorHelpers.h"

AmetempsychosisGameMode::AmetempsychosisGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
