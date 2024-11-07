// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"
#include "PawnNearNavArea.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UPawnNearNavArea : public UNavArea
{
	GENERATED_BODY()
public:
	UPawnNearNavArea(const FObjectInitializer& ObjectInitializer);
};
