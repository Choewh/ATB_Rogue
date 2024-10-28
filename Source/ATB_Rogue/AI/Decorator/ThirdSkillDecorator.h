// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/BaseBTDecorator.h"
#include "ThirdSkillDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UThirdSkillDecorator : public UBaseBTDecorator
{
	GENERATED_BODY()
	
public:
	UThirdSkillDecorator(const FObjectInitializer& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
