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
	//Rookie
	Guilmon UMETA(DisplayName = "Guilmon"),
	Plotmon UMETA(DisplayName = "Plotmon"),
	//Champion
	Growmon UMETA(DisplayName = "Growmon"),
	Tailmon UMETA(DisplayName = "Tailmon"),
	//Ultimate
	Megalogrowmon UMETA(DisplayName = "Megalogrowmon"),
	Angewomon UMETA(DisplayName = "Angewomon"),
	//Mege
	Dukemon UMETA(DisplayName = "Dukemon"),
	Ofanimon UMETA(DisplayName = "Ofanimon"),


	End UMETA(DisplayName = "End")
};
