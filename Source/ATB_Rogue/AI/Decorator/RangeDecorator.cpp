// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/RangeDecorator.h"
#include "Enums/Skills.h"
#include "AI/BaseAIController.h"
#include "RangeDecorator.h"

URangeDecorator::URangeDecorator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "RangeDecorator";
}

bool URangeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBehaviorTreeComponent* BehaviorTreeComponent = &OwnerComp;
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	const ESkills UseSkill = static_cast<ESkills>(BlackboardComponent->GetValueAsEnum("Skill"));

	ABaseAIController* BaseAIController = Cast<ABaseAIController>(BehaviorTreeComponent->GetOwner());
	ABasePawn* OwnerPawn = Cast<ABasePawn>(BaseAIController->GetPawn());
	ABasePawn* TargetPawn = BaseAIController->TargetPawn;
	if (!TargetPawn) { return false; }

	float Distance = FVector::Dist(OwnerPawn->GetActorLocation(), TargetPawn->GetActorLocation());
	switch (UseSkill)
	{
	case ESkills::None:
		return false;
	case ESkills::FirstSkill:
		if (Distance <= OwnerPawn->SkillComponent->FirstSkillData->Skill_Range)
		{
			return true;
		}
		return false;
	case ESkills::SecondSkill:
		if (Distance <= OwnerPawn->SkillComponent->SecondSkillData->Skill_Range)
		{
			return true;
		}
		return false;
	case ESkills::ThirdSkill: //3 ��ų�� �����ϴ��� üũ
		if (!OwnerPawn->SkillComponent->SkillData->Skill_3) { return false; }

		if (Distance <= OwnerPawn->SkillComponent->ThirdSkillData->Skill_Range)
		{
			return true;
		}
		return false;
	default:
		return false;
	}
}
