// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/FinishTurn.h"
#include "Subsystem/BattleSubsystem.h"
#include "FinishTurn.h"

UFinishTurn::UFinishTurn()
{
	NodeName = "FinishTurn";
	bTickIntervals = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UFinishTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}

	//조건을 추가해서 턴 종료 타이밍 조절 
	UObject* TargetPawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	ABasePawn* Target = Cast<ABasePawn>(TargetPawn);

	if (Target->OnDieCheck())
	{
		return EBTNodeResult::InProgress;
	}

	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->FinishTurn();
	
	//타겟폰이 없다면 그냥 성공 반환
	
	//타겟폰이 죽었다면 진행중 틱에서 타겟폰이 nullptr 이라면 성공 반환
	
	//아래는 그냥 디버그용

// 범위의 색상과 선 두께 설정
	FVector MovePoint = BlackboardComponent->GetValueAsVector(TEXT("MovePoint"));
	ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
	FColor TargetPawnColor = FColor::Green;
	FColor MovePointColor = FColor::Red;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정
	uint8 Skill = BlackboardComponent->GetValueAsEnum(TEXT("SKill"));

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), MovePoint, 100.f, 12, MovePointColor, false, Duration);
	if (Target)
	{
		DrawDebugSphere(GetWorld(), Target->GetActorLocation(), 100.f, 12, TargetPawnColor, false, Duration);
	}
	return EBTNodeResult::Succeeded;
}

void UFinishTurn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UObject* TargetPawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	ABasePawn* Target = Cast<ABasePawn>(TargetPawn);
	if (Target->IsDestroy())
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->FinishTurn();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
