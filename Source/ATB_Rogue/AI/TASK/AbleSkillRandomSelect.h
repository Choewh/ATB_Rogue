// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemyAIController.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "AbleSkillRandomSelect.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAbleSkillRandomSelect : public UBaseBTTaskNode
{
	GENERATED_BODY()
	UAbleSkillRandomSelect();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void EmptyCheck();
	void PickRandomSkill();
	void SelectAttackRandomPawn(ESkills Skill);
	void Init();
public:

	bool FirstEmpty = false;
	bool SecondEmpty = false;
	bool ThirdEmpty = false;

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
