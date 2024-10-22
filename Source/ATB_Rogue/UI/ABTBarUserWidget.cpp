// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABTBarUserWidget.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Kismet/GameplayStatics.h"
//#include "Pawn/BasePawn.h"


UABTBarUserWidget::UABTBarUserWidget()
{

}

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
	GetWorld()->GetSubsystem<UBattleSubsystem>()->DBattleStart.AddDynamic(this, &ThisClass::FindActivePawn);
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


void UABTBarUserWidget::OnATBChanged(float CurATB, float MaxATB)
{
	SetVisibility(ESlateVisibility::Visible);
	
}

void UABTBarUserWidget::FindActivePawn()
{
	TArray<AActor*> ActivePawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePawn::StaticClass(), ActivePawns);
	for(int i=0; i< ActivePawns.Num(); i++)
	{
		ABasePawn* BasePawn = Cast<ABasePawn>(ActivePawns[i]);
		BasePawn->OnATBChanged.AddDynamic(this, &ThisClass::OnATBChanged);
		FSlateBrush DisabledThumbImage;
		DisabledThumbImage.SetResourceObject(BasePawn->PawnData->Portraits);
		FSliderStyle SliderStyle;
		ATBbars[i]->SetWidgetStyle(SliderStyle.SetDisabledThumbImage(DisabledThumbImage));
		BasePawn->SetATBbar(ATBbars[i]);
		ATBbars[i]->SetVisibility(ESlateVisibility::Visible);
	}
}

