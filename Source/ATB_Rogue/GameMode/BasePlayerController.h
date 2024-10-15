// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Camera/CameraComponent.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ABasePlayerController();

	void BeginPlay();

public : 
	

public:

	//void OnMove(const FInputActionValue& InputActionValue);
	void OnRightClick(const FInputActionValue& InputActionValue);
	void SetupInputComponent();


public:

	UPROPERTY()
	UInputMappingContext* IMC;

	UPROPERTY()
	FVector TargetLocation;

	UCameraComponent* DefaultCamera;

	UCameraComponent* EnemyViewCamera;
};
