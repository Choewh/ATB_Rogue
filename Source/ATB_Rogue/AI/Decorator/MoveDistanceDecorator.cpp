// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/MoveDistanceDecorator.h"
#include "AI/BaseAIController.h"
#include "MoveDistanceDecorator.h"

UMoveDistanceDecorator::UMoveDistanceDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "MoveDistanceDecorator";
}

bool UMoveDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBehaviorTreeComponent* BehaviorTreeComponent = &OwnerComp;
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(BehaviorTreeComponent->GetOwner());
	ABasePawn* OwnerPawn = Cast<ABasePawn>(BaseAIController->GetPawn());
	FVector MovePoint = BlackboardComponent->GetValueAsVector(TEXT("MovePoint"));

	float Distance = FVector::Dist(OwnerPawn->GetActorLocation(), MovePoint);

	if (Distance > 300 && Distance < OwnerPawn->StatusComponent->GetSpeciesInfo()->MoveRange)
	{
		return true;
	}

	return false;
}
