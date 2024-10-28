// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/SetEnemyMovePonint.h"
#include "Pawn/BasePawn.h"
#include "Enums/Skills.h"

USetEnemyMovePonint::USetEnemyMovePonint()
{
	NodeName = "SetEnemyMovePonint";
}

EBTNodeResult::Type USetEnemyMovePonint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	UObject* Pawn = BlackboardComponent->GetValueAsObject(TEXT("TargetPawn"));
	if (!IsValid(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")))) { return EBTNodeResult::Failed; }

	ABasePawn* TargetPawn = Cast<ABasePawn>(Pawn);
	USkillComponent* SkillComponent = TargetPawn->SkillComponent;
	UStatusComponent* StatusComponent = TargetPawn->StatusComponent;
	float MoveRange = StatusComponent->GetMoveRange();
	ESkills Skill = static_cast<ESkills>(BlackboardComponent->GetValueAsEnum(TEXT("usableSkill")));
	float SkillRange = SkillComponent->GetSkillRange(Skill);
	FVector EnemyVec = AIOwner->GetPawn()->GetActorLocation();
	FVector TargetPawnVec = TargetPawn->GetActorLocation();

	FVector DirVec = TargetPawnVec - EnemyVec;

	float TargetDistance = FVector::Dist(EnemyVec, TargetPawnVec);
	FVector DirNormalVec = DirVec.GetSafeNormal();
	float randomValue = FMath::FRandRange(200.f, 400.f);
	FVector MovePoint = EnemyVec + (DirNormalVec * (TargetDistance - SkillRange + randomValue));

	BlackboardComponent->SetValueAsVector(TEXT("MovePoint"), MovePoint);

	if (BlackboardComponent->GetValueAsVector(TEXT("MovePoint")) == FVector::Zero())
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
