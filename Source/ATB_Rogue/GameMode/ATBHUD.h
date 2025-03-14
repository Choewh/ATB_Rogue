// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widget/ATBBarUserWidget.h"
#include "Widget/ATBBattleUserWidget.h"
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
	void AddPawnBattleUI(ABasePawn* InPawn);
	UFUNCTION()
	void RemovePawnBattleUI(ABasePawn* DeadPawn);
	UFUNCTION()
	void UpdatePawnUI(ABasePawn* UpdatePawn);

	UFUNCTION()
	void ShowBattleUI(uint8 Round);
	UFUNCTION()
	void ShowBattleUtilsUI(uint8 Round);
	UFUNCTION()
	void HideBattleUI();
	UFUNCTION()
	void HideBattleUtilsUI();

	UFUNCTION()
	void ShowTurnActionWidget();
	
	UFUNCTION()
	void HideTurnActionWidget();
	UFUNCTION()
	void ShowBattleMenuUI();
private:
	UPROPERTY()
	TObjectPtr<class ABasePlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<UATBBattleUserWidget> ATBBattleUserWidget;

	UPROPERTY()
	TObjectPtr<UATBUserWidget> TurnActionWidget;
	UPROPERTY()
	TObjectPtr<UATBUserWidget> BattleMenuUI;
	UPROPERTY()
	TObjectPtr<UATBUserWidget> BattleUtilsUI;

	/*UPROPERTY()
	TObjectPtr<UATBBarUserWidget> ATBWidget;*/

	

};
