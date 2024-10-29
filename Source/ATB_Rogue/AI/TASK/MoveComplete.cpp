// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/MoveComplete.h"
#include "Subsystem/BattleSubsystem.h"
#include "MoveComplete.h"

UMoveComplete::UMoveComplete()
{
	NodeName = "FinishTurn";
}

EBTNodeResult::Type UMoveComplete::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	FVector MovePoint = BlackboardComponent->GetValueAsVector(TEXT("MovePoint"));
	// 범위의 색상과 선 두께 설정
	FColor SphereColor = FColor::Green;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), MovePoint, 100.f, 12, SphereColor, false, Duration);

	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);
	BattleSubsystem->FinishTurn();

	return EBTNodeResult::Succeeded;
}
