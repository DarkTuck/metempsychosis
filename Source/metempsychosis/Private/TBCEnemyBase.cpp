// Fill out your copyright notice in the Description page of Project Settings.


#include "TBCEnemyBase.h"

ATBCEnemyBase::ATBCEnemyBase()
{
	Controler=CreateDefaultSubobject<UAIBattleControler>(TEXT("AIController"));
	bIsEnemyCharacter=true;
}
