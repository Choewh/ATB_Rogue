// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseFloatingPawnMovement.h"

UBaseFloatingPawnMovement::UBaseFloatingPawnMovement()
	: bOrientRotationToMovement(true)
{
	NavAgentProps.AgentRadius = 40.f;
	NavAgentProps.AgentHeight = 180.f;
}

void UBaseFloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


