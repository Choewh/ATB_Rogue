// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"

#include "Enums/Species.h"
#include "MainUserWidget.generated.h"

/**
 *
 */

class ABasePawn;

UCLASS()
class ATB_ROGUE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void CreateButtons(uint8 InNum);

protected:
	UFUNCTION()
	void SelectPawn(ESpecies SelectSpecies, UImage* Portrait);
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	void Init();

private:

	void SelectPawnsUpdata(UImage* Portrait);
	UFUNCTION(BlueprintCallable)
	void AddedPawnsDelete();
	UFUNCTION(BlueprintCallable)
	bool EnterGame();

private:

	UTexture2D* GetTexture2DFromImage(UImage* InImage);

	TArray<FName> SelectAblePawnNames;

	TArray<ESpecies> SelectPawns; //크기 300 300 /패딩 40

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UScrollBox* SelectBox;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* SelectPawn1;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* SelectPawn2;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* SelectPawn3;

};

