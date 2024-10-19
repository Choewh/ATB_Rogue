// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FEffectTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Effect")
	UStaticMesh* RangeMesh = nullptr;

};