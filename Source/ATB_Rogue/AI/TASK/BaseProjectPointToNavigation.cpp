// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/BaseProjectPointToNavigation.h"
#include "NavigationSystem.h"
#include "Pawn/BasePawn.h"

UBaseProjectPointToNavigation::UBaseProjectPointToNavigation()
{
    NodeName = "ProjectPointToNavigation";
}

EBTNodeResult::Type UBaseProjectPointToNavigation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

    ABasePawn* TargetPawn = Cast<ABasePawn>(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")));
    if (IsValid(TargetPawn))
    {
        FVector TargetLocation = TargetPawn->GetActorLocation();
        FNavLocation ClosestPoint;
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
        if (NavSystem->ProjectPointToNavigation(TargetLocation, ClosestPoint, FVector(200.0, 200.0, 200.0)))
        {
            BlackboardComponent->SetValueAsVector(TEXT("TargetPoint"), ClosestPoint.Location);
        }
    }

	return EBTNodeResult::Succeeded;
}
