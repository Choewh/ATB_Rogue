// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "EnemyRangeInFriendly.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UEnemyRangeInFriendly : public UBaseBTTaskNode
{
	GENERATED_BODY()
	UEnemyRangeInFriendly();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	void Init();
	void SkillRangeCheck();
	void UnableSkill(uint8 SkillNum);
public:
	bool FindPawn = false;
	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
