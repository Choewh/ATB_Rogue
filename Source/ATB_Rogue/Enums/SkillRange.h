// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ESkillRange : uint8
{
	Long UMETA(DisplayName = "Long"),
	Short UMETA(DisplayName = "Short"),
};
	