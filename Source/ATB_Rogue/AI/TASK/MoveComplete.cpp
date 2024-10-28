// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/MoveComplete.h"
#include "Subsystem/BattleSubsystem.h"
#include "MoveComplete.h"

UMoveComplete::UMoveComplete()
{
	NodeName = "MoveComplete";
}

EBTNodeResult::Type UMoveComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);
	BattleSubsystem->FinishTurn();

	return EBTNodeResult::Succeeded;
}
