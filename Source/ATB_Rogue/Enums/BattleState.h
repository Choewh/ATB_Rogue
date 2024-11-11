// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EBattleState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Move UMETA(DisplayName = "Move"),
	Attack UMETA(DisplayName = "Attack"),
	Wait UMETA(DisplayName = "Wait"),
	Finish UMETA(DisplayName = "Finish"),
	Evolution UMETA(DisplayName = "Evolution"),
};
