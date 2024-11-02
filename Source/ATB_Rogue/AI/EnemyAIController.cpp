// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"
#include "EnemyAIController.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/BT_Enemy.BT_Enemy'"));
		check(BT);
		RunBehaviorTree(BT);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	if (!BasePawn) { return; }

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

