// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "Pawn/BasePawn.h"
#include "Data/SkillTableRow.h"
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

	void UseSkillSet(ESkills UseSkill);
	float DamageCalculation(FSkillTableRow* UseSkillData); // 스킬의 데이터 테이블 ㅇ //타겟 , 계수 , 타수 (최소댐 ~ 최대댐) 
protected:

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
	
	UPROPERTY(EditAnywhere , Category = Node)
	ESkills UseSkillSelect;

	USkillComponent* SkillComponent;

	UStatusComponent* StatusComponent;


	
	
};
