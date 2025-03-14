// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Forward declaration

#include "Component/StatusComponent.h"
#include "Component/SkillComponent.h"
#include "Pawn/BasePawn.h"

#include "BaseAIController.generated.h"


/**
 * 
 */
UCLASS()
class ATB_ROGUE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;



protected:
	UFUNCTION()
	void OnDamaged(float CurrentHP, float MaxHP);	


	UFUNCTION()
	void ResetValue();

public:
	UFUNCTION()
	void SetActiveTurn(bool ActiveTurn);

public:
	UPROPERTY()
	ABasePawn* TargetPawn;
protected:
	UPROPERTY()
	UStatusComponent* StatusComponentRef;
	USkillComponent* SkillComponentRef;
};
