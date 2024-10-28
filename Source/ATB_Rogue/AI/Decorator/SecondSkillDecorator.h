// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/BaseBTDecorator.h"
#include "SecondSkillDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API USecondSkillDecorator : public UBaseBTDecorator
{
	GENERATED_BODY()
public:
	USecondSkillDecorator(const FObjectInitializer& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
