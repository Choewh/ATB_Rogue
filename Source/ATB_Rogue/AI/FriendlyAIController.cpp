// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FriendlyAIController.h"
#include "FriendlyAIController.h"


void AFriendlyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/BT_Friendly.BT_Friendly'"));
		check(BT);
		RunBehaviorTree(BT);
	}
}

void AFriendlyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	if (!BasePawn) { return; }
	BasePawn->OnMove.AddDynamic(this, &ThisClass::SetMovePoint);
}

void AFriendlyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFriendlyAIController::SetMovePoint(FVector MovePoint)
{
	Blackboard->SetValueAsBool(TEXT("bMove"), true);
	Blackboard->SetValueAsVector(TEXT("MovePoint"), MovePoint);
}
