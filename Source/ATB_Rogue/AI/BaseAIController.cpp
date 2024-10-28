// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Pawn/BasePawn.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	if (!BasePawn) { return; }
	StatusComponentRef = BasePawn->GetComponentByClass<UStatusComponent>();
	SkillComponentRef = BasePawn->GetComponentByClass<USkillComponent>();
	BasePawn->OnMove.AddDynamic(this, &ThisClass::SetMovePoint);
	// StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* OwningPawn = GetPawn();
	ABasePawn* BasePawn = Cast<ABasePawn>(OwningPawn);
}

void ABaseAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}

//컨트롤러 -> 폰 -> 배틀
void ABaseAIController::SetMovePoint(FVector MovePoint)	
{
	Blackboard->SetValueAsVector(TEXT("MovePoint"), MovePoint);
	Blackboard->SetValueAsBool(TEXT("bMove"), true);
	//Task 호출
}

void ABaseAIController::ResetValue()
{

}
