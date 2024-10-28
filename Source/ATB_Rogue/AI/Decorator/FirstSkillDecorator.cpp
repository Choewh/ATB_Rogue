// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/FirstSkillDecorator.h"

UFirstSkillDecorator::UFirstSkillDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "FirstSkillDecorator";
}

bool UFirstSkillDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bSkill3")))
	{
		return false;
	}
	return true;
}
