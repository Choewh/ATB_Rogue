// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "SplineCameraChildActorComponent.generated.h"

UCLASS()
class ATB_ROGUE_API USplineCameraChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USplineCameraChildActorComponent();
	void SetData(FDataTableRowHandle InDataTableRowHandle);
	
};
