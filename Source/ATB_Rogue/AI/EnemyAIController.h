// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "Pawn/BasePawn.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AEnemyAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetActiveTurn(bool ActiveTurn);

	TArray<ABasePawn*> FirstSkillRangePawns;
	TArray<ABasePawn*> SecondSkillRangePawns;
	TArray<ABasePawn*> ThirdSkillRangePawns;
	ABasePawn* TargetPawn;
};
