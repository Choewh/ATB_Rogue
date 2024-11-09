// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ATBBattleUserWidget.h"
#include "Components/OverlaySlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Border.h"


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
	// NewPawn 생성시 호출 
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

	UOverlay* ProgressBarBox = NewObject<UOverlay>(this);
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

	//EnemyBarBox 설정
	EnemyBarBox->AddChild(ProgressBarBox);
	{
		ProgressBarBox->AddChild(Image);
		ProgressBarBox->AddChild(VerticalBox);
		TArray<UPanelSlot*> Slots = ProgressBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Image->GetBrush();

		BrushCopy.SetImageSize(FVector2D(200.f, 50.f));

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
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	//빨강
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);
	//노랑
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);


	
	//EnemyPortraitBox 설정
	UImage* Portrait = NewObject<UImage>(this);
	EnemyPortraitBox->AddChild(Portrait);
	{
		TArray<UPanelSlot*> Slots = EnemyPortraitBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Portrait->GetBrush();

		BrushCopy.SetImageSize(FVector2D(100.f, 100.f));

		Portrait->SetBrush(BrushCopy);
		Portrait->SetBrushFromTexture(InEnemyPawn->GetPortrait());
	}

	FPawnUIElements PawnUIElements;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;
	PawnUIElements.Portrait = Portrait;

	EnemyUI.Add(InEnemyPawn, PawnUIElements);
}



void UATBBattleUserWidget::AddFriendlyUI(ABasePawn* InFriendlyPawn)
{
	UOverlay* ProgressBarBox = NewObject<UOverlay>(this);
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

	//FriendlyBarBox 설정
	FriendlyBarBox->AddChild(ProgressBarBox);
	{
		ProgressBarBox->AddChild(Image);
		ProgressBarBox->AddChild(VerticalBox);
		TArray<UPanelSlot*> Slots = ProgressBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Image->GetBrush();

		BrushCopy.SetImageSize(FVector2D(200.f, 50.f));

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
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
	}
	//빨강
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);
	//노랑
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);



	//FriendlyPortraitBox 설정
	UOverlay* PortraitBox = NewObject<UOverlay>(this);
	UBorder* PortraitBorder = NewObject<UBorder>(this);
	UImage* Portrait = NewObject<UImage>(this);
	FriendlyPortraitBox->AddChild(PortraitBox);

	PortraitBox->AddChild(PortraitBorder);
	PortraitBorder->AddChild(Portrait);

	{
		TArray<UPanelSlot*> Slots = FriendlyPortraitBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = Portrait->GetBrush();

		BrushCopy.SetImageSize(FVector2D(100.f, 100.f));

		Portrait->SetBrush(BrushCopy);
		Portrait->SetBrushFromTexture(InFriendlyPawn->GetPortrait());
	}
	//구조체 생성
	FPawnUIElements PawnUIElements;

	TWeakObjectPtr<UOverlay> WeakProgressBarBoxPtr;
	WeakProgressBarBoxPtr = ProgressBarBox;

	PawnUIElements.ProgressBarBox = WeakProgressBarBoxPtr;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;

	TWeakObjectPtr<UOverlay> WeakPortraitBoxPtr;
	WeakPortraitBoxPtr = ProgressBarBox;

	PawnUIElements.PortraitBox = WeakPortraitBoxPtr;
	PawnUIElements.Portrait = Portrait;

	FriendlyUI.Add(InFriendlyPawn, PawnUIElements);
}

void UATBBattleUserWidget::RemovePawnUI(ABasePawn* DeadPawn)
{
	// NewPawn 생성시 호출 
	switch (DeadPawn->PawnGroup)
	{
	case EPawnGroup::Enemy:
		RemoveEnemyUI(DeadPawn);
		break;

	case EPawnGroup::Friendly:
		RemoveFriendlyUI(DeadPawn);
		break;
	default:
		break;
	}
}

void UATBBattleUserWidget::RemoveEnemyUI(ABasePawn* DeadPawn)
{
	if (DeadPawn && EnemyUI.Contains(DeadPawn))
	{
		// UI 요소 삭제 처리
		FPawnUIElements* UIElements = EnemyUI.Find(DeadPawn);
		if (UIElements)
		{
			if (UIElements->PortraitBox.IsValid())
			{
				UIElements->PortraitBox->RemoveFromParent();
			}
			if (UIElements->ProgressBarBox.IsValid())
			{
				UIElements->ProgressBarBox->RemoveFromParent();
			}
		}
		// EnemyUI에서 삭제
		EnemyUI.Remove(DeadPawn);
	}
}

void UATBBattleUserWidget::RemoveFriendlyUI(ABasePawn* DeadPawn)
{

}
