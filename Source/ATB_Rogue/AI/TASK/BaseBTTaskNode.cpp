// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBTTaskNode.h"

UBaseBTTaskNode::UBaseBTTaskNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
void UBaseBTTaskNode::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIOwner = Cast<AAIController>(InActorOwner);
}
