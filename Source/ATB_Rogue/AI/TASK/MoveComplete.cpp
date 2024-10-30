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
	UObject* TargetPawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	ABasePawn* BasePawn = Cast<ABasePawn>(TargetPawn);
	uint8 Skill = BlackboardComponent->GetValueAsEnum(TEXT("SKill"));
	
	// 범위의 색상과 선 두께 설정
	FColor TargetPawnColor = FColor::Green;
	FColor MovePointColor = FColor::Red;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), MovePoint, 100.f, 12, MovePointColor, false, Duration);
	DrawDebugSphere(GetWorld(), BasePawn->GetActorLocation(), 100.f, 12, TargetPawnColor, false, Duration); 
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>(); // 공격 구현후 지우기 ㅇ
	BattleSubsystem->FinishTurn(); //														<<
	BlackboardComponent->SetValueAsBool(TEXT("bMove"), false);

	UE_LOG(LogTemp, Log, TEXT("Uint Value: %u, String Value: %s"), Skill, *BasePawn->GetName());
	
	return EBTNodeResult::Succeeded;
}
