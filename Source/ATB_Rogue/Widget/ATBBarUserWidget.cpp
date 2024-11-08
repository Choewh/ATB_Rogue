// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ATBBarUserWidget.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/BasePawn.h"

void UATBBarUserWidget::NativeOnInitialized()
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

void UATBBarUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UATBBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UATBBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UATBBarUserWidget::OnHiddenUI()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UATBBarUserWidget::OnDie()
{
}

