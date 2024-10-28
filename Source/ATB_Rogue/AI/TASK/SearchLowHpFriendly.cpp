// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/SearchLowHpFriendly.h"
#include "AI/EnemyAIController.h"
#include "SearchLowHpFriendly.h"

USearchLowHpFriendly::USearchLowHpFriendly()
{
	NodeName = "SearchLowHpFriendly";
}

EBTNodeResult::Type USearchLowHpFriendly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(AIOwner);

	if (BlackboardComponent->GetValueAsBool(TEXT("bSkillAttackable3"))) FindLowHpPawn(EnemyAIController->ThirdSkillRangePawns, ESkills::ThirdSkill);
	if (BlackboardComponent->GetValueAsBool(TEXT("bSkillAttackable2"))) FindLowHpPawn(EnemyAIController->SecondSkillRangePawns, ESkills::SecondSkill);
	if (BlackboardComponent->GetValueAsBool(TEXT("bSkillAttackable1"))) FindLowHpPawn(EnemyAIController->FirstSkillRangePawns, ESkills::FirstSkill);

	if (LowHpPawn != nullptr)
	{
		BlackboardComponent->SetValueAsObject(TEXT("TargetPawn"), LowHpPawn);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void USearchLowHpFriendly::FindLowHpPawn(TArray<ABasePawn*> InPawns , ESkills Skill)
{
	for (ABasePawn* Pawn : InPawns)
	{	//임시
		float PawnHP = Pawn->StatusComponent->GetStat(EStat::HP);
		if (LowHpPawn != nullptr)
		{
			float LowPawnHP = LowHpPawn->StatusComponent->GetStat(EStat::HP);
			if (PawnHP < LowPawnHP)
			{
				LowHpPawn = Pawn;
				BlackboardComponent->SetValueAsEnum(TEXT("usableSkill"), static_cast<uint8>(Skill));
			}
		}
		else
		{
			LowHpPawn = Pawn;
		}
	}
}

