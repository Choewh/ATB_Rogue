// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EHitDamageType : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Special UMETA(DisplayName = "Special"),
};
