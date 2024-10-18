// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EDigimonType : uint8
{
	Data UMETA(DisplayName = "Data"),
	Vaccine UMETA(DisplayName = "Vaccine"),
	Virus UMETA(DisplayName = "Virus"),
};
