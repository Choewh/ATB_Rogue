// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Species.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ESpecies : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	//BabyI
	Jyarimon UMETA(DisplayName = "Jyarimon"),
	//BabyII
	Gigimon UMETA(DisplayName = "Gigimon"),
	//Rookie
	Guilmon UMETA(DisplayName = "Guilmon"),
	//Champion
	Growmon UMETA(DisplayName = "Growmon"),
	//Ultimate
	Megalogrowmon UMETA(DisplayName = "Megalogrowmon"),
	//Mege
	Dukemon UMETA(DisplayName = "Dukemon"),
	End UMETA(DisplayName = "End")
};
