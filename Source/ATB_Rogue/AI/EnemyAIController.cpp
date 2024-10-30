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
	BasePawn->ActiveTurn.AddDynamic(this, &ThisClass::SetActiveTurn);

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AEnemyAIController::SetActiveTurn(bool ActiveTurn)
{
	Blackboard->SetValueAsBool(TEXT("bAction"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bMove"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bAttack"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable1"), !ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable2"), !ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable3"), !ActiveTurn);
}