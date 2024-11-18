// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BaseFloatingPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseFloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
public:

	UBaseFloatingPawnMovement();
	virtual FRotator GetDeltaRotation(float DeltaTime) const;
	void SetUseControllerRotationYaw(bool Active);
	virtual bool IsFalling() const override;
	virtual bool IsMovingOnGround() const override;
protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PhysicsRotation(float DeltaTime);
	virtual FRotator ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const;

	virtual bool CheckFalling(float DeltaTime);
	virtual FVector NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const;


	UPROPERTY()
	FVector AccelerationAdvance;

	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	uint8 bOrientRotationToMovement : 1;
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	FRotator RotationRate;

	bool bFalling = false;
	float FallingDeltaTime = 0.f;
};
