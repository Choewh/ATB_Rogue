// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/AttackComplete.h"
#include "Pawn/BasePawn.h"
#include "AttackComplete.h"
#include "Kismet/KismetSystemLibrary.h"
UAttackComplete::UAttackComplete()
{
	NodeName = "AttackComplete";
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UAttackComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}

	bool bMontagePlaying = BlackboardComponent->GetValueAsBool(TEXT("MontagePlaying"));
	UE_LOG(LogTemp, Log, TEXT("bMontagePlaying: %s"), bMontagePlaying ? TEXT("True") : TEXT("False"));
	if (bMontagePlaying)
	{
		return EBTNodeResult::InProgress;
	}
	BlackboardComponent->SetValueAsBool(TEXT("bAttack"), false);

	return EBTNodeResult::Succeeded;
}

void UAttackComplete::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool bMontagePlaying = BlackboardComponent->GetValueAsBool(TEXT("MontagePlaying"));
	if (!bMontagePlaying)
	{
		UE_LOG(LogTemp, Log, TEXT("bMontagePlaying: %s"), bMontagePlaying ? TEXT("True") : TEXT("False"));
		BlackboardComponent->SetValueAsBool(TEXT("bAttack"), false);

		//타겟폰이 죽었으면 죽는 모션까지 다 보고 끝날 수 있게하기 1.플래그 세우기 피니시턴에서
		//ABasePawn* TargetPawn = Cast<ABasePawn>(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")));
		//bool bDie = TargetPawn->OnDieCheck();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
