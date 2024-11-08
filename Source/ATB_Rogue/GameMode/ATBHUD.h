// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widget/ATBBarUserWidget.h"
#include "ATBHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AATBHUD : public AHUD
{
	GENERATED_BODY()
public:
	AATBHUD();


public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:


	UFUNCTION()
	void ShowATBBar(uint8 Round);
	UFUNCTION()
	void ShowViewPort();

private:
	UPROPERTY()
	TObjectPtr<class ABasePlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<class UATBUserWidget> Widget;

	UPROPERTY()
	TObjectPtr<UATBBarUserWidget> ATBWidget;

	

};
