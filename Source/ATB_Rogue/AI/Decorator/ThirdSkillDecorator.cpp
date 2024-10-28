// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/ThirdSkillDecorator.h"

UThirdSkillDecorator::UThirdSkillDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "ThirdSkillDecorator";
}

bool UThirdSkillDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bSkill3")))
	{
		return false;
	}
	return true;
}
