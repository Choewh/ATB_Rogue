// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/MoveComplete.h"
#include "MoveComplete.h"

UMoveComplete::UMoveComplete()
{
	NodeName = "FinishTurn";
}

EBTNodeResult::Type UMoveComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	

	BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);
	
	return EBTNodeResult::Succeeded;
}
