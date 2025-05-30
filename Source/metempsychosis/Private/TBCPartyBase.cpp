// Fill out your copyright notice in the Description page of Project Settings.


#include "TBCPartyBase.h"

ATBCPartyBase::ATBCPartyBase(): Controler(nullptr)
{
	Controler=CreateDefaultSubobject<UAIBattleControler>(TEXT("AIController"));
	bIsEnemyCharacter=false;
}

void ATBCPartyBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (bIsPlayer)
	{
		Controler->Deactivate();
	}
}
