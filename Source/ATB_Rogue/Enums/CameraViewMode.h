// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ECameraViewMode : uint8
{
	DefaultView UMETA(DisplayName = "DefaultView"),
	PawnView UMETA(DisplayName = "PawnView"),
};
