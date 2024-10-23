// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BasePawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBasePawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	UBasePawnMovementComponent();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	uint8 bOrientRotationToMovement : 1;
};
