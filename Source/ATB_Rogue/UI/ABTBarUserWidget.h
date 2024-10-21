// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/ABTUserWidget.h"
#include "Components/Slider.h"
#include "ABTBarUserWidget.generated.h"

/**
 * 
 */


UCLASS()
class ATB_ROGUE_API UABTBarUserWidget : public UABTUserWidget
{
	GENERATED_BODY()
	
public:
	void RegisterPortrait();
};
