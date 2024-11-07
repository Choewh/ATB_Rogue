// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/OnSpawnMoveComplete.h"
#include "AI/BaseAIController.h"
#include "Pawn/BasePawn.h"

UOnSpawnMoveComplete::UOnSpawnMoveComplete()
{
	NodeName = "OnSpawnMoveComplete";
}

EBTNodeResult::Type UOnSpawnMoveComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	BlackboardComponent->SetValueAsBool(TEXT("bSpawn"), false);

	return EBTNodeResult::Succeeded;
}

void UOnSpawnMoveComplete::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
