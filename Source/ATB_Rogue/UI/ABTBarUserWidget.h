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


UCLASS()
class ATB_ROGUE_API UABTBarUserWidget : public UABTUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void OnHiddenUI();
	UFUNCTION()
	void OnATBChanged(float CurrentHP, float MaxHP);
	UFUNCTION()
	void OnDie();
public:
	UFUNCTION()
	void SetPortrait(UTexture2D* Portrait);
protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* ATBbar;
};
