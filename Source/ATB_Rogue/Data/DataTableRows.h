// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Misc/Utils.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "Actor/BaseCameraSplineActor.h"

#include "DataTableRows.generated.h"
/**
 * 
 */
class ATB_ROGUE_API DataTableRows
{
public:
	DataTableRows();
	~DataTableRows();
};

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
	TSubclassOf<ABaseCameraSplineActor> CameraSplineClass;
public:
	/*
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	TSubclassOf<UShapeComponent> CollisionClass = USphereComponent::StaticClass();
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 44.f;
	*/
public: // UAnimMontage
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> DieMontage;

//public: // Movement
//	UPROPERTY(EditAnywhere, Category = "Pawn|Movement")
//	float MovementMaxSpeed = 400.f;

public:
//public: // AI
//	UPROPERTY(EditAnywhere, Category = "Pawn|AI")
//	TSubclassOf<AAIController> AIControllerClass;
};
