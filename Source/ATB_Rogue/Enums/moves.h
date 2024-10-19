// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EMoves: uint8
{
	None UMETA(DisplayName = "None"),
	TestMagic UMETA(DisplayName = "TestMagic"),
	TestMelee UMETA(DisplayName = "TestMelee"),
};
	