// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/RangeDecorator.h"
#include "RangeDecorator.h"

URangeDecorator::URangeDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "RangeDecorator";
}

bool URangeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	return false;
}
