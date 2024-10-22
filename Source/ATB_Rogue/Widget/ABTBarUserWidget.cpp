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
	for (int i =0; i<(BattleSubsystem->Pawns.Num()); i++)
	{
		FSlateBrush DisabledThumbImage;        
		DisabledThumbImage.SetResourceObject(BattleSubsystem->Pawns[i]->PawnData->Portraits);

		//아웃라인
		FSlateBrushOutlineSettings OutlineSettings;
		OutlineSettings.Width = 5.f;
		switch (BattleSubsystem->Pawns[i]->PawnGroup)
		{
		case EPawnGroup::Enemy:
			OutlineSettings.Color = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case EPawnGroup::Friendly:
			OutlineSettings.Color = FSlateColor(FLinearColor(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		}
		DisabledThumbImage.DrawAs = ESlateBrushDrawType::RoundedBox;
		DisabledThumbImage.SetImageSize(FVector2D(100,100)); 
		DisabledThumbImage.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)); // 반투명 빨간색
		FSliderStyle SliderStyle;
		
		SliderStyle.SetDisabledThumbImage(DisabledThumbImage);
		
		ATBbars[i]->SetWidgetStyle(SliderStyle);
		{
		}
		ATBbars[i]->IsFocusable = false;
	}
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

