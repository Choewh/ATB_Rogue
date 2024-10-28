// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBaseBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	UBaseBTDecorator(const FObjectInitializer& ObjectInitializer);

};
