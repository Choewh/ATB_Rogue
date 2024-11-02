// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RotatorCharMoveComponent.h"
#include "RotatorCharMoveComponent.h"

URotatorCharMoveComponent::URotatorCharMoveComponent()
{
	bOrientRotationToMovement = true;
	bUseControllerDesiredRotation = false;
	RotationRate = FRotator(0.0f, 90.0f, 0.0f);
}

void URotatorCharMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}
