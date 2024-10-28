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
}

void AFriendlyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
