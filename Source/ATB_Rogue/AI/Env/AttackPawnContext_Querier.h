// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "AttackPawnContext_Querier.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAttackPawnContext_Querier : public UEnvQueryContext_Querier
{
	GENERATED_BODY()
	
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
