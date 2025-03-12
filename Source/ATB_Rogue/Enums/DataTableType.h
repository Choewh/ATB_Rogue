#pragma once

#include "CoreMinimal.h"
/**
 *
 */
UENUM(BlueprintType)
enum class EDataTableType: uint8
{
	/** Pawn */
	Pawn		UMETA(DisplayName = "Pawn"),
	/** Status */
	Status		UMETA(DisplayName = "Status"), 
	/** Skill */
	Skill		UMETA(DisplayName = "Skill"),
	/** Effect */
	Effect		UMETA(DisplayName = "Effect"),
	/** Animation */
	Animation	UMETA(DisplayName = "Animation"),
};
	