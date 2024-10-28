// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/SecondSkillDecorator.h"

USecondSkillDecorator::USecondSkillDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "SecondSkillDecorator";
}

bool USecondSkillDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bSkill3")))
	{
		return false;
	}
	return true;
}
