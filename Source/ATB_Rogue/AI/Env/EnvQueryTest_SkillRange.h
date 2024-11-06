// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Enums/Skills.h"
#include "EnvQueryTest_SkillRange.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UEnvQueryTest_SkillRange : public UEnvQueryTest
{
	GENERATED_BODY()

	UEnvQueryTest_SkillRange(const FObjectInitializer& ObjectInitializer);

	/** context */
	UPROPERTY(EditDefaultsOnly, Category = Distance)
	TSubclassOf<UEnvQueryContext> DistanceTo;

	UPROPERTY(EditDefaultsOnly, Category = UseSkill)
	ESkills UseSkill;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionDetails() const override;
};
