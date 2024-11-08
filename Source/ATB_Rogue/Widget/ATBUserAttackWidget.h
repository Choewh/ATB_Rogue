// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/ATBUserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
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

	void SetImage();
public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* FirstSkillImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USelectableCell* FirstSkillCell;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* SecondSkillImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USelectableCell* SecondSkillCell;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* ThirdSkillImage;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USelectableCell* ThirdSkilICell;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* Portrait;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* Cancle;
};
