// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"

#include "Enums/Species.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */

class ABasePawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFindPortraitFromName, UImage* , Image , FName, SpeciesName);

UCLASS()
class ATB_ROGUE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void CreateButtons(uint8 InNum);

protected:
	UFUNCTION()
	void OnButtonClicked();
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	void Init();

private:
	UPROPERTY(BlueprintAssignable)
	FFindPortraitFromName SetSpeciesPortrait;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UScrollBox* SelectBox;

	ESpecies SelectSpecies;

	TArray<ABasePawn*> SelectPawns; //크기 300 300 /패딩 40


};

