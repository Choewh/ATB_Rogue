// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "ShowTurnActionWidgetTASK.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UShowTurnActionWidgetTASK : public UBaseBTTaskNode
{
	GENERATED_BODY()
	
	UShowTurnActionWidgetTASK();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
