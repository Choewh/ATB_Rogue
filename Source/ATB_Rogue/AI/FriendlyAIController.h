// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "FriendlyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AFriendlyAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
};
