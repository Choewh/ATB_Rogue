// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Misc/Utils.h"
#include "Data/SkillTableRows.h"
#include "Data/EffectTableRows.h"
#include "Data/StatTableRows.h"
#include "Data/AnimMontageTableRows.h"

#include "Actor/BaseCameraSplineActor.h"

#include "DataTableRows.generated.h"
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
		CameraSplineClass(nullptr),
		Effect(), // Effect의 기본값 설정 (필요시)
		Stat()    // Stat의 기본값 설정
	{

	}
public:
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
public:
	UPROPERTY(EditAnywhere, Category = "Effect" , meta = (RowType = "/Script/ATB_ROGUE.EffectTableRow"))
	FDataTableRowHandle Effect;
public:
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (RowType = "/Script/ATB_ROGUE.StatTableRow"))
	FDataTableRowHandle Stat; 


};
