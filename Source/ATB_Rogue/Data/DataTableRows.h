// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Misc/Utils.h"
#include "Data/SkillTableRows.h"
#include "Data/EffectTableRows.h"
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

};
