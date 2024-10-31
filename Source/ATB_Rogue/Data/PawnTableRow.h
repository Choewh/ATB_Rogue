	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Engine/Texture2D.h"
#include "Misc/Utils.h"
#include "Enums/Species.h"
#include "Components/BoxComponent.h"

#include "AIController.h"
#include "Actor/BaseCameraSplineActor.h"

#include "PawnTableRow.generated.h"
/**
 * 
 */

USTRUCT()
struct ATB_ROGUE_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Species")
	ESpecies Species;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Species")
	ESpecies NextSpecies; // 지금은 단일 루트인데 여러개로 늘어나면 테이블로 관리

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Portrait")
	UTexture2D* Portraits;
public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	FTransform MeshTransform = FTransform::Identity;


	UPROPERTY(EditAnywhere, Category = "Pawn")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	TSubclassOf<UShapeComponent> CollisionClass = UBoxComponent::StaticClass();

	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 150.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 150.f;		


	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AAIController> EnemyAIController;
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AAIController> FriendlyAIController;
		
	UPROPERTY(EditAnywhere, Category = "Pawn")
	TSubclassOf<ABaseCameraSplineActor> CameraSplineClass = ABaseCameraSplineActor::StaticClass();


};
