// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/BaseBTTask_MoveTo.h"
#include "Subsystem/BattleSubsystem.h"
#include "BaseBTTask_MoveTo.h"

UBaseBTTask_MoveTo::UBaseBTTask_MoveTo()
{
		NodeName = "MoveTo_Delegate";
		bCreateNodeInstance = true;
		bTickIntervals = true;
		bNotifyTick = true;
}


EBTNodeResult::Type UBaseBTTask_MoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);
	BehaviorTreeComponent = &OwnerComp;
	AActor* Actor = OwnerComp.GetOwner();
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	switch (NodeResult)
	{
	case EBTNodeResult::Succeeded:
		BlackboardComponent->SetValueAsBool(TEXT("bSpawn"), false);
		break;
	default:
		break;
	}
	return NodeResult;
}

