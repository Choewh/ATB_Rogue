// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "AttackComplete.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAttackComplete : public UBaseBTTaskNode
{
	GENERATED_BODY()
	UAttackComplete();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
