// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/BasePawn.h"
#include "FriendlyPawn.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AFriendlyPawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	AFriendlyPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void SetData() override;

	bool Movealbe(FVector NewDestination);
	void MoveTo(FVector NewDestination);
	bool OnAutoPlay(bool Active);

private:
	bool bAuto = false;
};
