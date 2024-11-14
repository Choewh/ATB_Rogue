// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EEvolutionLevel: uint8
{
	ChampionEvolution		UMETA(DisplayName = "ChampionEvolution"),
	UltimateEvolution		UMETA(DisplayName = "UltimateEvolution"),
	MegaEvolution		UMETA(DisplayName = "MegaEvolution"),
};
	