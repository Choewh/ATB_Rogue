// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/ShowTurnActionWidgetTASK.h"
#include "Subsystem/BattleSubsystem.h"
#include "ShowTurnActionWidgetTASK.h"

UShowTurnActionWidgetTASK::UShowTurnActionWidgetTASK()
{
	NodeName = "ShowTurnActionWidgetTASK";
}

EBTNodeResult::Type UShowTurnActionWidgetTASK::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}

	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->SelectActionView();

	return EBTNodeResult::Succeeded;
}
