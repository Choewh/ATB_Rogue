// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EBattleSpec : uint8
{
	Default UMETA(DisplayName = "Default"),
	Boss UMETA(DisplayName = "Boss"),
};
