// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EStat: uint8
{
	/** Hit Points */
	HP		UMETA(DisplayName = "HP"), 
	/** Attack */
	ATK		UMETA(DisplayName = "ATK"),
	/** Defense */
	DEF		UMETA(DisplayName = "DEF"),
	/** Special Attack */
	SPATK	UMETA(DisplayName = "SPATK"),
	/** Special Defense */
	SPDEF	UMETA(DisplayName = "SPDEF"),
	/** Speed */
	SPD		UMETA(DisplayName = "SPD"),
	/** Accuracy */
	ACC		 UMETA(DisplayName = "ACC"),
	/** Evasiveness */
	EVA		 UMETA(DisplayName = "EVA"),
};
	