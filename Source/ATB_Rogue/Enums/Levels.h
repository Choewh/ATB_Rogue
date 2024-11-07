// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ELevels : uint8
{
	None UMETA(DisplayName = "None"),
	Start UMETA(DisplayName = "Start"),
	FirstLevel UMETA(DisplayName = "FirstLevel"),
	SecondLevel UMETA(DisplayName = "SecondLevel"),
};
	