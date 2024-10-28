// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ESkills : uint8
{
	None UMETA(DisplayName = "None"),
	FirstSkill UMETA(DisplayName = "FirstSkill"),
	SecondSkill UMETA(DisplayName = "SecondSkill"),
	ThirdSkill UMETA(DisplayName = "ThirdSkill"),
};
	