// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceDirector.h"
#include "EvolutionSequenceDirector.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UEvolutionSequenceDirector : public ULevelSequenceDirector
{
	GENERATED_BODY()
public:
	virtual void OnCreated();
};
