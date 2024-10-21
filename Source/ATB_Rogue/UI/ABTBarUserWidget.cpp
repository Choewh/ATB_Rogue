// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABTBarUserWidget.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
//#include "Pawn/BasePawn.h"

void UABTBarUserWidget::NativeOnInitialized()
{
}

void UABTBarUserWidget::NativePreConstruct()
{
}

void UABTBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	class ABasePawn* Pawn = Cast<ABasePawn>(GetOwningPawn());
	check(Pawn);
	Pawn->OnATBChanged.AddDynamic(this, &ThisClass::OnATBChanged);
	// Pawn->HideATBbar 추가하기 죽엇을때 or 배틀중이 아닐때 호출
	SetVisibility(ESlateVisibility::Hidden);
}

void UABTBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UABTBarUserWidget::OnHiddenUI()
{
	//ATB 바 가리기
}

void UABTBarUserWidget::SetPortrait(UTexture2D* Portrait)
{
	FSlateBrush DisabledThumbImage;
	DisabledThumbImage.SetResourceObject(Portrait);
	FSliderStyle SliderStyle;
	ATBbar->SetWidgetStyle(SliderStyle.SetDisabledThumbImage(DisabledThumbImage));
}

void UABTBarUserWidget::OnATBChanged(float CurrentATB, float MaxATB)
{
	SetVisibility(ESlateVisibility::Visible);
	const float Percent = CurrentATB / MaxATB;
	ATBbar->SetValue(Percent);
}

void UABTBarUserWidget::OnDie()
{
}
