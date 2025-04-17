// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(Meta=(Category="AttackType"))
enum class EAttackType : uint8
{
	Physical    UMETA(DisplayName = "Physical"),
	Fire       UMETA(DisplayName = "Fire"),
	Electricity UMETA(DisplayName = "Electricity"),
	Wind       UMETA(DisplayName = "Wind"),
	Light      UMETA(DisplayName = "Light"),
	Darkness   UMETA(DisplayName = "Darkness")
};

