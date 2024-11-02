// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/BaseBTDecorator.h"
#include "RangeDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API URangeDecorator : public UBaseBTDecorator
{
	GENERATED_BODY()
	
public:
	URangeDecorator(const FObjectInitializer& ObjectInitializer);

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
