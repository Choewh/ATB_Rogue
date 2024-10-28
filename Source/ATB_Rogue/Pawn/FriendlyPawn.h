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
	AFriendlyPawn(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetData() override;
	
};
