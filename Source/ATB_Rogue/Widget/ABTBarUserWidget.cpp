// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ABTBarUserWidget.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/BasePawn.h"

void UABTBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ATBbars.Add(ATBbar_0);
	ATBbars.Add(ATBbar_1);
	ATBbars.Add(ATBbar_2);
	ATBbars.Add(ATBbar_3);
	ATBbars.Add(ATBbar_4);
	ATBbars.Add(ATBbar_5);
	ATBbars.Add(ATBbar_6);
	ATBbars.Add(ATBbar_7);
	ATBbars.Add(ATBbar_8);
	ATBbars.Add(ATBbar_9);

}

void UABTBarUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UABTBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UABTBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UABTBarUserWidget::OnHiddenUI()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UABTBarUserWidget::OnDie()
{
}

