// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "ABTHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AABTHUD : public AHUD
{
	GENERATED_BODY()
public:
	AABTHUD();

public:
	virtual void BeginPlay() override;

public:


	//UFUNCTION()
	//void ShowATBBar(UTexture2D* Portrait);
	UFUNCTION()
	void ShowViewPort();

private:

	UPROPERTY()
	TObjectPtr<class ABasePlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<class UABTUserWidget> Widget;

	UPROPERTY()
	TObjectPtr<class UABTUserWidget> ATBWidget;

	

};
