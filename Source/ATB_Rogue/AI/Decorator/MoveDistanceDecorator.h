// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/BaseBTDecorator.h"
#include "MoveDistanceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UMoveDistanceDecorator : public UBaseBTDecorator
{
	GENERATED_BODY()
public:
	UMoveDistanceDecorator(const FObjectInitializer& ObjectInitializer);

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
