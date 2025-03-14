// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BaseBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseBTTaskNode : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	public:


	virtual void SetOwner(AActor* InActorOwner) override;

protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> AIOwner;

	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AActor> ActorOwner;
};
