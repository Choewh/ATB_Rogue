// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EAttribute : uint8
{
	None UMETA(DisplayName = "None"),
	Vaccine UMETA(DisplayName = "Vaccine"),
	Data UMETA(DisplayName = "Data"),
	Virus UMETA(DisplayName = "Virus"),
	Unknown UMETA(DisplayName = "Unknown"),
};
