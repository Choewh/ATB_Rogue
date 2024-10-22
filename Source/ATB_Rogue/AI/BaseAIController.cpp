// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Pawn//BasePawn.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseAIController::BeginPlay()
{
	if (!BrainComponent)
	{
		UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/BT_Pawn.BT_Pawn'"));
		check(BT);
		RunBehaviorTree(BT);
	}

}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	StatusComponentRef = BasePawn->GetComponentByClass<UStatusComponent>();
	BasePawn->OnMove.AddDynamic(this, &ThisClass::SetMovePoint);
	// StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged); 피격시 델리게이트 호출
}

void ABaseAIController::Tick(float DeltaTime)
{
}

void ABaseAIController::OnDamaged(float CurrentHP, float MaxHP)
{
	//데미지 계산 ㅇㅇ
}

void ABaseAIController::ResetOnDamaged()
{

}

void ABaseAIController::SetMovePoint(FVector MovePoint)
{
	Blackboard->SetValueAsVector(TEXT("MovePoint"), MovePoint);
}

void ABaseAIController::ResetValue()
{

}
