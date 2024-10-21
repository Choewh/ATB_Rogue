// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Species.h"
#include "EffectTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FEffectTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Species")
	ESpecies Species;
	UPROPERTY(EditAnywhere, Category = "Effect|RangeDecal")
	UMaterial* RangeDecalMaterial;
	UPROPERTY(EditAnywhere, Category = "Effect|RangeDecal")
	FTransform RangeDecalTransform;
};