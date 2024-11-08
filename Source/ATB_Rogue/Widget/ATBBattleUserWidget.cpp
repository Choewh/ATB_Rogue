// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ATBBattleUserWidget.h"
#include "Components/OverlaySlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Overlay.h"

void UATBBattleUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UATBBattleUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UATBBattleUserWidget::AddPawnUI(ABasePawn* InBasePawn)
{
	// NewPawn »ý¼º½Ã È£Ãâ 
	switch (InBasePawn->PawnGroup)
	{
	case EPawnGroup::Enemy:
		AddEnemyUI(InBasePawn);
		break;

	case EPawnGroup::Friendly:
		AddFriendlyUI(InBasePawn);
		break;
	default:
		break;
	}
}

void UATBBattleUserWidget::AddEnemyUI(ABasePawn* InEnemyPawn)
{
	UOverlay* BoxOverlay = NewObject<UOverlay>(this);
	UImage* Image = NewObject<UImage>(this);
	UVerticalBox* VerticalBox = NewObject<UVerticalBox>(this);
	UOverlay* HPOverlay = NewObject<UOverlay>(this);
	UOverlay* ATBOverlay = NewObject<UOverlay>(this);
	UProgressBar* HPProgressBar = NewObject<UProgressBar>(this);
	UProgressBar* ATBProgressBar = NewObject<UProgressBar>(this);

	VerticalBox->SetIsEnabled(false);
	Image->SetIsEnabled(false);
	HPProgressBar->SetIsEnabled(false);
	ATBProgressBar->SetIsEnabled(false);

	EnemyBarBox->AddChild(BoxOverlay);
	{
		BoxOverlay->AddChild(Image);
		BoxOverlay->AddChild(VerticalBox);
		TArray<UPanelSlot*> Slots = BoxOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Image->GetBrush();

		BrushCopy.SetImageSize(FVector2D(200.f, 30.f));

		Image->SetBrush(BrushCopy);
	}
	{
		VerticalBox->AddChild(HPOverlay);
		VerticalBox->AddChild(ATBOverlay);
		TArray<UPanelSlot*> Slots = VerticalBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(OverlaySlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	{
		HPOverlay->AddChild(HPProgressBar);
		TArray<UPanelSlot*> Slots = HPOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
	}
	{
		ATBOverlay->AddChild(ATBProgressBar);
		TArray<UPanelSlot*> Slots = ATBOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
	}
	{
		TArray<UPanelSlot*> Slots = EnemyBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(OverlaySlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	//»¡°­
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);
	//³ë¶û
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);

	FPawnUIElements PawnUIElements;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;
	PawnUIElements.Image = Image;

	EnemyUI.Add(InEnemyPawn, PawnUIElements);
}


void UATBBattleUserWidget::AddFriendlyUI(ABasePawn* InFriendlyPawn)
{
	UOverlay* BoxOverlay = NewObject<UOverlay>(this);
	UImage* Image = NewObject<UImage>(this);
	UVerticalBox* VerticalBox = NewObject<UVerticalBox>(this);
	UOverlay* HPOverlay = NewObject<UOverlay>(this);
	UOverlay* ATBOverlay = NewObject<UOverlay>(this);
	UProgressBar* HPProgressBar = NewObject<UProgressBar>(this);
	UProgressBar* ATBProgressBar = NewObject<UProgressBar>(this);

	VerticalBox->SetIsEnabled(false);
	Image->SetIsEnabled(false);
	HPProgressBar->SetIsEnabled(false);
	ATBProgressBar->SetIsEnabled(false);

	FriendlyBarBox->AddChild(BoxOverlay);
	{
		BoxOverlay->AddChild(Image);
		BoxOverlay->AddChild(VerticalBox);
		TArray<UPanelSlot*> Slots = BoxOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Image->GetBrush();

		BrushCopy.SetImageSize(FVector2D(200.f, 30.f));

		Image->SetBrush(BrushCopy);
	}
	{
		VerticalBox->AddChild(HPOverlay);
		VerticalBox->AddChild(ATBOverlay);
		TArray<UPanelSlot*> Slots = VerticalBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(OverlaySlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	{
		HPOverlay->AddChild(HPProgressBar);
		TArray<UPanelSlot*> Slots = HPOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
	}
	{
		ATBOverlay->AddChild(ATBProgressBar);
		TArray<UPanelSlot*> Slots = ATBOverlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
	}
	{
		TArray<UPanelSlot*> Slots = FriendlyBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(OverlaySlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	//»¡°­
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);
	//³ë¶û
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);

	FPawnUIElements PawnUIElements;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;
	PawnUIElements.Image = Image;

	FriendlyUI.Add(InFriendlyPawn, PawnUIElements);
}
