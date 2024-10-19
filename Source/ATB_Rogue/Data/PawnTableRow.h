// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Misc/Utils.h"

#include "Enums/Species.h"

#include "Data/SkillTableRow.h"
#include "Data/EffectTableRow.h"
#include "Data/StatTableRow.h"
#include "Data/AnimMontageTableRow.h"

#include "Actor/BaseCameraSplineActor.h"

#include "PawnTableRow.generated.h"
/**
 * 
 */
USTRUCT()
struct ATB_ROGUE_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FPawnTableRow()
		: SkeletalMesh(nullptr),
		MeshTransform(FTransform::Identity),
		AnimClass(nullptr),
		CameraSpline(nullptr),
		BPCameraSpline(nullptr),
		CameraSplineClass(nullptr)
	{

	}
public:
	UPROPERTY(EditAnywhere, Category = "Species")
	ESpecies Species;
	UPROPERTY(EditAnywhere, Category = "Portrait")
	TArray<UTexture*> Portraits;
public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	TSubclassOf<UAnimInstance> AnimClass;
public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	TObjectPtr<ABaseCameraSplineActor> CameraSpline;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	TObjectPtr<USplineComponent> BPCameraSpline;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	TSubclassOf<ABaseCameraSplineActor> CameraSplineClass;

//public:
//	UPROPERTY(EditAnywhere, Category = "Effect" , meta = (RowType = "/Script/ATB_ROGUE.EffectTableRow"))
//	FDataTableRowHandle Effect;
//public:
//	UPROPERTY(EditAnywhere, Category = "Stat", meta = (RowType = "/Script/ATB_ROGUE.StatTableRow"))
//	FDataTableRowHandle Stat; 


};
