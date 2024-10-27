// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */

UENUM(BlueprintType)
enum class EPawnState : uint8
{
	Defalut UMETA(DisplayName = "Default"),
	Move UMETA(DisplayName = "Move"),
	Attack UMETA(DisplayName = "Attack")
};
