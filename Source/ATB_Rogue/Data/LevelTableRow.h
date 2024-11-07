	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enums/Species.h"
#include "Enums/Levels.h"

#include "LevelTableRow.generated.h"
/**
 * 
 */

USTRUCT()
struct ATB_ROGUE_API FLevelTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Species")
	ELevels Levels;

	//
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Species")
	TArray<ESpecies> Species;

};
