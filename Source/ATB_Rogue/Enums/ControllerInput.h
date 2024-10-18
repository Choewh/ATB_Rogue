// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EControllerInput : uint8
{
	Default UMETA(DisplayName = "Default"),
	MouseRight UMETA(DisplayName = "MouseRight"),
	MouseLeft UMETA(DisplayName = "MouseLeft"),
};
