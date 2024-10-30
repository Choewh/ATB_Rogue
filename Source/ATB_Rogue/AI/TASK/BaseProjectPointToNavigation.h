// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "BaseProjectPointToNavigation.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseProjectPointToNavigation : public UBaseBTTaskNode
{
	GENERATED_BODY()
	UBaseProjectPointToNavigation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
