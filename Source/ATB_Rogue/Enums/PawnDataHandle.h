// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EPawnDataHandle : uint8
{
	Effect UMETA(DisplayName = "Effect"),
	Stat UMETA(DisplayName = "Stat"),
};
	