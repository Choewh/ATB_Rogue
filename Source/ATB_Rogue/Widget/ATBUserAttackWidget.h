// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/ATBUserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Widget/USelectableCell.h"
#include "ATBUserAttackWidget.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UATBUserAttackWidget : public UATBUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	void Init();
	UFUNCTION(BlueprintCallable)
	void ShowSkillRange(ESkills UseSkill);
private:
	UFUNCTION()
	void FinishTurn();
	
	void CreateSkillUI();

public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* SkillHorizontalBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skills")
	UButton* FirstSkillCell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skills")
	UButton* SecondSkillCell;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skills")
	UButton* ThirdSkillCell;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USelectableCell* Cancle;
private:
	UTexture2D* SkillBG;
};
