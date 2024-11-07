// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/BasePawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	AEnemyPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
	virtual void SetData() override;
};
