// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/ABTUserWidget.h"
#include "Components/Slider.h"
#include "Engine/Texture2D.h"
#include "ABTBarUserWidget.generated.h"

/**
 *
 */
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSliderUpdate, USlider*, Caller, float, NewValue);

UCLASS()
class ATB_ROGUE_API UABTBarUserWidget : public UABTUserWidget
{
	GENERATED_BODY()

public:
	UABTBarUserWidget();
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void OnATBChanged(float CurrentHP, float MaxHP);

	UFUNCTION()
	void FindActivePawn();

	FSliderUpdate SliderUpdate;
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<USlider*> ATBbars;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_0;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_1;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_3;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_4;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_5;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_6;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_7;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_8;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar_9;
};
