// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RotatorCharMoveComponent.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API URotatorCharMoveComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	

public:

	URotatorCharMoveComponent();
protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
