// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/ATBUserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/Slider.h"
#include "ATBBattleUserWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPawnUIElements
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<USlider> SliderBar;
	UPROPERTY()
	TWeakObjectPtr<UOverlay> PortraitBox;

	UPROPERTY()
	TWeakObjectPtr<UImage> Portrait;

	UPROPERTY()
	TWeakObjectPtr<UOverlay> ProgressBarBox;
	UPROPERTY()
	TWeakObjectPtr<UProgressBar> HPProgressBar;

	UPROPERTY()
	TWeakObjectPtr<UProgressBar> ATBProgressBar;
};

UCLASS()
class ATB_ROGUE_API UATBBattleUserWidget : public UATBUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void AddPawnUI(ABasePawn* InBasePawn);
	void AddEnemyUI(ABasePawn* InEnemyPAwn);
	void AddFriendlyUI(ABasePawn* InFriendlyPAwn);

	void RemovePawnUI(ABasePawn* DeadPawn);
	void RemoveEnemyUI(ABasePawn* DeadPawn);
	void RemoveFriendlyUI(ABasePawn* DeadPawn);
	
	UFUNCTION()
	void OnPortraitUpdate(ABasePawn* UpdatePawn);
	UFUNCTION()
	void OnHPBarUpdate(ABasePawn* InPawn, float InPercent);
	UFUNCTION()
	void OnATBBarUpdate(ABasePawn* InPawn, float InPercent);



private:
	UPROPERTY()
	TMap<TWeakObjectPtr<ABasePawn>, FPawnUIElements> EnemyUI;
	UPROPERTY()
	TMap<TWeakObjectPtr<ABasePawn>, FPawnUIElements> FriendlyUI;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* ATBBarBox;
	///
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UVerticalBox* EnemyBarBox;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UVerticalBox* EnemyPortraitBox;
	/// 
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UVerticalBox* FriendlyPortraitBox;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UVerticalBox* FriendlyBarBox;
};
