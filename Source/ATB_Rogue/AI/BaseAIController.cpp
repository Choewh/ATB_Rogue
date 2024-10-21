// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	if (!BrainComponent)
	{
		//UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/BT_Pawn.BT_Pawn'"));
		//check(BT);
		//RunBehaviorTree(BT);
	}
}

void ABaseAIController::BeginPlay()
{
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
}

void ABaseAIController::Tick(float DeltaTime)
{
}
