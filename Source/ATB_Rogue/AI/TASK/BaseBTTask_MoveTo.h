// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseBTTask_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseBTTask_MoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
private:
	UBaseBTTask_MoveTo(const FObjectInitializer& ObjectInitializer);
	virtual void SetOwner(AActor* InActorOwner) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AAIController> AIOwner;

	/** Cached actor owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	TObjectPtr<AActor> ActorOwner;

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
