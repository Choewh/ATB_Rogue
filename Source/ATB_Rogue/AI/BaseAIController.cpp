// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
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
	//BasePawn->ActiveTurn.AddDynamic(this, &ThisClass::SetActiveTurn); //���̽� ���� �Ͻ��� �Ͽ��� ��������Ʈ �߰��ؼ� ȣ�����ֱ� 
	// StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* OwningPawn = GetPawn();

	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();

	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);
}

void ABaseAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}


void ABaseAIController::ResetValue()
{

}

void ABaseAIController::SetActiveTurn(bool ActiveTurn)
{
	TargetPawn = nullptr;
	Blackboard->SetValueAsObject(TEXT("TargetPawn"), TargetPawn);
	Blackboard->SetValueAsVector(TEXT("MovePoint"), GetPawn()->GetActorLocation());
	Blackboard->SetValueAsEnum(TEXT("Skill"), 0);
	Blackboard->SetValueAsBool(TEXT("bAction"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bMove"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bAttack"), ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), !ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable1"), !ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable2"), !ActiveTurn);
	Blackboard->SetValueAsBool(TEXT("bSkillAttackable3"), !ActiveTurn);
}
