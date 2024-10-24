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
	UBaseBTTask_MoveTo();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
