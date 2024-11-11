// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EPawnGroup : uint8
{
	Default UMETA(DisplayName = "Default"),
	Friendly UMETA(DisplayName = "Friendly"),
	Enemy UMETA(DisplayName = "Enemy")
};
