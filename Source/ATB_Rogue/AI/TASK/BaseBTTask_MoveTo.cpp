// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/BaseBTTask_MoveTo.h"
#include "Subsystem/BattleSubsystem.h"
#include "BaseBTTask_MoveTo.h"

UBaseBTTask_MoveTo::UBaseBTTask_MoveTo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UBaseBTTask_MoveTo::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIOwner = Cast<AAIController>(InActorOwner);
}

EBTNodeResult::Type UBaseBTTask_MoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	switch (NodeResult)
	{
	case EBTNodeResult::Succeeded:
		BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);
		BattleSubsystem->FinishTurn();
		break;
	default:
		break;
	}
	return NodeResult;
}

