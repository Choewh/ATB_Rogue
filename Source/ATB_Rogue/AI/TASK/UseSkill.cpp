// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/UseSkill.h"
#include "UseSkill.h"

UUseSkill::UUseSkill()
{
	
	NodeName = "UseSkill";
	
}

EBTNodeResult::Type UUseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	return EBTNodeResult::Succeeded;
}
