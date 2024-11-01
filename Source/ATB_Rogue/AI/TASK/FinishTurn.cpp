// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/FinishTurn.h"
#include "Subsystem/BattleSubsystem.h"
#include "FinishTurn.h"

UFinishTurn::UFinishTurn()
{
	NodeName = "FinishTurn";

}

EBTNodeResult::Type UFinishTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}

	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->FinishTurn();

	//아래는 그냥 디버그용

// 범위의 색상과 선 두께 설정
	FVector MovePoint = BlackboardComponent->GetValueAsVector(TEXT("MovePoint"));
	UObject* TargetPawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	ABasePawn* Target = Cast<ABasePawn>(TargetPawn);
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
		UE_LOG(LogTemp, Log, TEXT("Uint Value: %u, String Value: %s"), Skill, *Target->GetName());
	}
	return EBTNodeResult::Succeeded;


	return EBTNodeResult::Succeeded;
}