// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/LookAt.h"
#include "Kismet/KismetMathLibrary.h"
#include "Subsystem/BattleSubsystem.h"
#include "LookAt.h"

ULookAt::ULookAt()
{
	NodeName = "LookAt";
}

EBTNodeResult::Type ULookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	FVector StartPoint = AIOwner->GetPawn()->GetActorLocation();
	FVector TargetPoint = BlackboardComponent->GetValueAsVector(TEXT("TargetPoint"));
	AActor* TargetPawn = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")));

	if (!TargetPawn) { return EBTNodeResult::Failed; }

	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		BattleSubsystem->SetViewCameraMode(ECameraViewMode::Attack);
	}
	TargetPoint = TargetPawn->GetActorLocation();

	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartPoint, TargetPoint);
	AIOwner->GetPawn()->SetActorRotation(LookAtRotator);
	return EBTNodeResult::Succeeded;
}
