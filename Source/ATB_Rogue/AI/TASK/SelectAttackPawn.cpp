// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/SelectAttackPawn.h"
#include "SelectAttackPawn.h"

USelectAttackPawn::USelectAttackPawn()
{
	NodeName = "SelectAttackPawn";
}

EBTNodeResult::Type USelectAttackPawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	

	return EBTNodeResult::Succeeded;
}
