// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "Enums/Skills.h"
#include "Enums/SkillRange.h"
#include "UseSkill.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UUseSkill : public UBaseBTTaskNode
{
	GENERATED_BODY()
	UUseSkill();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
	
	UPROPERTY(EditAnywhere , Category = Node)
	ESkills UseSkillSelect;

	UPROPERTY(EditAnywhere , Category = Node)
	ESkillRange SkillRangeType;


	
	
};
