// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stage.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EStage: uint8
{
	None		UMETA(DisplayName = "None"),
	BabyI		UMETA(DisplayName = "BabyI"),
	BabyII		UMETA(DisplayName = "BabyII"),
	Rookie		UMETA(DisplayName = "Rookie"),
	Champion	UMETA(DisplayName = "Champion"),
	Ultimate	UMETA(DisplayName = "Ultimate"),
	Mega		UMETA(DisplayName = "Mega"),
};
	