// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/MoveComplete.h"
#include "Pawn/BasePawn.h"
#include "MoveComplete.h"

UMoveComplete::UMoveComplete()
{
	NodeName = "FinishTurn";
}

EBTNodeResult::Type UMoveComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}

	BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);
	
	//����׿� �߰�
	UObject* TargetPawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	if (TargetPawn)
	{
		ABasePawn* Target = Cast<ABasePawn>(TargetPawn);
		FVector MovePoint = BlackboardComponent->GetValueAsVector(TEXT("MovePoint"));
		ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
		const float Distance = FVector::Dist(Pawn->GetActorLocation(), Target->GetActorLocation());
		UE_LOG(LogTemp, Display, TEXT("Distance : %f"),Distance);
		UE_LOG(LogTemp, Display, TEXT("MovePoint : %s"), *MovePoint.ToString());
	}

	return EBTNodeResult::Succeeded;
}
