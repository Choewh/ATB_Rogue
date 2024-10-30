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
	ABasePawn* Enemy = Cast<AEnemyPawn>(AIOwner->GetPawn());
	USkillComponent* SkillComponent = Enemy->SkillComponent;
	UStatusComponent* StatusComponent = Enemy->StatusComponent;
	float MoveRange = StatusComponent->GetMoveRange();

	TArray<float> Range;
	bool Has3 = false;
	if (!SkillComponent->SpeciesSkillData->Skill_3) // 3스킬 유무
	{
		Range.Add(SkillComponent->GetSkillRange(ESkills::FirstSkill));
		Range.Add(SkillComponent->GetSkillRange(ESkills::SecondSkill));
	}
	else
	{
		Range.Add(SkillComponent->GetSkillRange(ESkills::FirstSkill));
		Range.Add(SkillComponent->GetSkillRange(ESkills::SecondSkill));
		Range.Add(SkillComponent->GetSkillRange(ESkills::ThirdSkill));
		Has3 = true;
	}

	for (uint8 i = 0; i < Range.Num(); i++)
	{
		TArray<FHitResult> HitResults;
		TArray<AActor*> IgnoreActors;
		UKismetSystemLibrary::SphereTraceMultiByProfile(ActorOwner, Enemy->GetActorLocation(), Enemy->GetActorLocation(),
			MoveRange + Range[i], TEXT("Friendly"), false, IgnoreActors, EDrawDebugTrace::None,
			HitResults, true);
		if (!HitResults.IsEmpty())
		{
			UnableSkill(i);
		}
		TArray<ABasePawn*> HitPawns;

		for (auto& HitResult : HitResults)
		{
			ABasePawn* HitPawn = Cast<ABasePawn>(HitResult.GetActor());
			if (HitPawn)
			{
				HitPawns.Add(HitPawn);
			}
		}
		AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(AIOwner);

		if (!HitPawns.IsEmpty())
		{
			switch (i)
			{
			case 0:
				EnemyAIController->FirstSkillRangePawns = HitPawns;
				FindPawn = true;
				break;
			case 1:
				EnemyAIController->SecondSkillRangePawns = HitPawns;
				FindPawn = true;
				break;
			case 2:
				EnemyAIController->ThirdSkillRangePawns = HitPawns;
				FindPawn = true;
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
