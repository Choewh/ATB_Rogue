// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/EnemyRangeInFriendly.h"
#include "AI/EnemyAIController.h"
#include "Component/SkillComponent.h"
#include "Component/StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pawn/EnemyPawn.h"
#include "EnemyRangeInFriendly.h"

UEnemyRangeInFriendly::UEnemyRangeInFriendly()
{
	NodeName = "EnemyRangeInFriendly";
}

EBTNodeResult::Type UEnemyRangeInFriendly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	Init();

	SkillRangeCheck();

	if (!FindPawn)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

void UEnemyRangeInFriendly::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}



void UEnemyRangeInFriendly::Init()
{
	FindPawn = false;
}

void UEnemyRangeInFriendly::SkillRangeCheck()
{
	ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
	Pawn->GetController();
	USkillComponent* SkillComponent = Pawn->SkillComponent;
	UStatusComponent* StatusComponent = Pawn->StatusComponent;
	float MoveRange = StatusComponent->GetSpeciesInfo()->MoveRange;

	TArray<float> Range;
	bool Has3 = false;
	if (!SkillComponent->SpeciesSkillData->Skill_3) // 3스킬 유무
	{
		Range.Add(SkillComponent->GetSkillData(ESkills::FirstSkill)->Skill_Range);
		Range.Add(SkillComponent->GetSkillData(ESkills::SecondSkill)->Skill_Range);
	}
	else
	{
		Range.Add(SkillComponent->GetSkillData(ESkills::FirstSkill)->Skill_Range);
		Range.Add(SkillComponent->GetSkillData(ESkills::SecondSkill)->Skill_Range);
		Range.Add(SkillComponent->GetSkillData(ESkills::ThirdSkill)->Skill_Range);
		Has3 = true;
	}

	for (uint8 i = 0; i < Range.Num(); i++)
	{
		TArray<FHitResult> HitResults;
		TArray<AActor*> IgnoreActors;
		if (Pawn->PawnGroup == EPawnGroup::Enemy)
		{
			UKismetSystemLibrary::SphereTraceMultiByProfile(ActorOwner, Pawn->GetActorLocation(), Pawn->GetActorLocation(),
				MoveRange + Range[i], TEXT("FriendlyTarget"), false, IgnoreActors, EDrawDebugTrace::None,
				HitResults, true);
		}
		else if (Pawn->PawnGroup == EPawnGroup::Friendly)
		{
			UKismetSystemLibrary::SphereTraceMultiByProfile(ActorOwner, Pawn->GetActorLocation(), Pawn->GetActorLocation(),
				MoveRange + Range[i], TEXT("EnemyTarget"), false, IgnoreActors, EDrawDebugTrace::None,
				HitResults, true);
		}
	
		TArray<ABasePawn*> HitPawns;

		for (auto& HitResult : HitResults)
		{
			ABasePawn* HitPawn = Cast<ABasePawn>(HitResult.GetActor());
			if (HitPawn)
			{
				HitPawns.Add(HitPawn);
				UnableSkill(i);
				FindPawn = true;
			}
		}

		AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(AIOwner);

		if (!HitPawns.IsEmpty())
		{
			switch (i)
			{
			case 0:
				EnemyAIController->FirstSkillRangePawns = HitPawns;
				break;
			case 1:
				EnemyAIController->SecondSkillRangePawns = HitPawns;
				break;
			case 2:
				EnemyAIController->ThirdSkillRangePawns = HitPawns;
				break;
			default:
				break;
			}
		}
	}
	//(HitResult, CameraLocation, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void UEnemyRangeInFriendly::UnableSkill(uint8 SkillNum)
{
	switch (SkillNum)
	{
	case 0:
		BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable1"), true);
		break;
	case 1:
		BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable2"), true);
		break;
	case 2:
		BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable3"), true);
		break;
	default:
		break;
	}
}
