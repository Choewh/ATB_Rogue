// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EControllerInput : uint8
{
	None UMETA(DisplayName = "None"),
	MouseRight UMETA(DisplayName = "MouseRight"),
	MouseLeft UMETA(DisplayName = "MouseLeft"),
};
