// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BasePawnMovementComponent.h"
#include "BasePawnMovementComponent.h"


UBasePawnMovementComponent::UBasePawnMovementComponent()
	: bOrientRotationToMovement(true)
{
	NavAgentProps.AgentRadius = 40.f;
	NavAgentProps.AgentHeight = 180.f;
}

void UBasePawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}