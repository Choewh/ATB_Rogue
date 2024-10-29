// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Pawn/BasePawn.h"
#include "BaseEnvQueryItemType_Actor.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseEnvQueryItemType_Actor : public UEnvQueryItemType_Actor
{
	GENERATED_BODY()
	
public:
	static void SetContextHelper(FEnvQueryContextData& ContextData, const ABasePawn* SingleActor);
	static void SetContextHelper(FEnvQueryContextData& ContextData, const TArray<ABasePawn*>& MultipleActors);
};
