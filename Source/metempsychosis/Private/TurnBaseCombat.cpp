// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseCombat.h"

void UTurnBaseCombat::StarCombat()
{
	return GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Trigger Fight");
}
