// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TASK/BaseBTTaskNode.h"
#include "Enums/Skills.h"
#include "Pawn/BasePawn.h"
#include "SearchLowHpFriendly.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API USearchLowHpFriendly : public UBaseBTTaskNode
{
	GENERATED_BODY()
	
public:
	USearchLowHpFriendly();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void FindLowHpPawn(TArray<ABasePawn*> InPawns, ESkills Skill);
private:
	ABasePawn* LowHpPawn;
public:

	class UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;
};
