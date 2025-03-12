// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "Misc/Datas.h"

#include "AnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATB_ROGUE_API UAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

public:
	virtual void SetData(ESpecies InSpecies);

public:
	FAnimMontageTableRow* AnimData;
};
