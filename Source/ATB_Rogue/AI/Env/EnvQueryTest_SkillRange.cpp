// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Env/EnvQueryTest_SkillRange.h"
#include "Pawn/BasePawn.h"
#include "AI/BaseAIController.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

#include "Kismet/KismetSystemLibrary.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(EnvQueryTest_SkillRange)

#define ENVQUERYTEST_DISTANCE_NAN_DETECTION 1

namespace
{
	FORCEINLINE float CalcDistance3D(const FVector& PosA, const FVector& PosB)
	{
		// Static cast this to a float, for EQS scoring purposes float precision is OK.
		return static_cast<float>(FVector::Distance(PosA, PosB));
	}

	FORCEINLINE float CalcDistance2D(const FVector& PosA, const FVector& PosB)
	{
		// Static cast this to a float, for EQS scoring purposes float precision is OK.
		return static_cast<float>(FVector::Dist2D(PosA, PosB));
	}

	FORCEINLINE float CalcDistanceZ(const FVector& PosA, const FVector& PosB)
	{
		// Static cast this to a float, for EQS scoring purposes float precision is OK.
		return static_cast<float>(PosB.Z - PosA.Z);
	}

	FORCEINLINE float CalcDistanceAbsoluteZ(const FVector& PosA, const FVector& PosB)
	{
		// Static cast this to a float, for EQS scoring purposes float precision is OK.
		return static_cast<float>(FMath::Abs(PosB.Z - PosA.Z));
	}
}

UEnvQueryTest_SkillRange::UEnvQueryTest_SkillRange(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DistanceTo = UEnvQueryContext_Querier::StaticClass();
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEnvQueryTest_SkillRange::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();

	if (QueryOwner == nullptr)
	{
		return;
	}

	ABasePawn* QueryPawn = Cast<ABasePawn>(QueryOwner);
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(QueryPawn->GetController());
	ABasePawn* TargetPawn = BaseAIController->TargetPawn;
	if (QueryPawn == nullptr)
	{
		return;
	}
	
	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();


	switch (UseSkill)
	{
	case ESkills::None:
		break;
	case ESkills::FirstSkill:
		MaxThresholdValue = QueryPawn->SkillComponent->FirstSkillData->Skill_Range;
		break;
	case ESkills::SecondSkill:
		MaxThresholdValue = QueryPawn->SkillComponent->SecondSkillData->Skill_Range;
		break;
	case ESkills::ThirdSkill:
		MaxThresholdValue = QueryPawn->SkillComponent->ThirdSkillData->Skill_Range;
		break;
	default:
		break;
	}
	///TEMP DEbug
	TArray<FHitResult> HitResults;
	TArray<AActor*> IgnoreActors;
	UKismetSystemLibrary::SphereTraceMultiByProfile(QueryPawn, TargetPawn->GetActorLocation(), TargetPawn->GetActorLocation(),
		MaxThresholdValue, TEXT("Enemy"), false, IgnoreActors, EDrawDebugTrace::ForDuration,
		HitResults, true);
	UKismetSystemLibrary::SphereTraceMultiByProfile(QueryPawn, TargetPawn->GetActorLocation(), TargetPawn->GetActorLocation(),
		MinThresholdValue, TEXT("Enemy"), false, IgnoreActors, EDrawDebugTrace::ForDuration,
		HitResults, true);
	UKismetSystemLibrary::SphereTraceMultiByProfile(QueryPawn, TargetPawn->GetActorLocation(), TargetPawn->GetActorLocation(),
		1200.f, TEXT("Enemy"), false, IgnoreActors, EDrawDebugTrace::ForDuration,
		HitResults, true);
	UE_LOG(LogTemp, Log, TEXT("PawnName : % s , MaxThresholdValue : %f"),*QueryPawn->GetName(), MaxThresholdValue);

	MaxThresholdValue -= 100.f;
	///TEMP
	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(DistanceTo, ContextLocations))
	{
		return;
	}


	// 커스텀 거리 계산 로직
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
		{
			const float Distance = FVector::Dist(ItemLocation, ContextLocations[ContextIndex]);
			It.SetScore(TestPurpose, FilterType, Distance, MinThresholdValue, MaxThresholdValue);
			if (Distance <= MaxThresholdValue)
			{
				int Check=0;
			}
		}
	}
}

FText UEnvQueryTest_SkillRange::GetDescriptionDetails() const
{
	return DescribeFloatTestParams();
}
