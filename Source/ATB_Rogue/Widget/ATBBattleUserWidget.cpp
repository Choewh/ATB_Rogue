// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ATBBattleUserWidget.h"
#include "Components/OverlaySlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Border.h"



void UATBBattleUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Resource/UI_Gimic_3_Card_Data.UI_Gimic_3_Card_Data'"));
		check(Texture);
		DataTexture = Texture;
	}
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Resource/UI_Gimic_3_Card_Vaccine.UI_Gimic_3_Card_Vaccine'"));
		check(Texture);
		VaccineTexture = Texture;
	}
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Resource/UI_Gimic_3_Card_Virus.UI_Gimic_3_Card_Virus'"));
		check(Texture);
		VirusTexture = Texture;
	}
}

void UATBBattleUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UATBBattleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UATBBattleUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UATBBattleUserWidget::AddPawnUI(ABasePawn* InBasePawn)
{
	// NewPawn ������ ȣ�� 
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
	if (!InEnemyPawn) { return; }

	InEnemyPawn->OnChangedATBBar.AddDynamic(this, &ThisClass::OnATBBarUpdate);
	InEnemyPawn->OnChangedHPBar.AddDynamic(this, &ThisClass::OnHPBarUpdate);

	UOverlay* ProgressBarBox = NewObject<UOverlay>(this);
	UImage* Image = NewObject<UImage>(this);
	UVerticalBox* VerticalBox = NewObject<UVerticalBox>(this);
	UOverlay* HPOverlay = NewObject<UOverlay>(this);
	UOverlay* ATBOverlay = NewObject<UOverlay>(this);
	UProgressBar* HPProgressBar = NewObject<UProgressBar>(this);
	UProgressBar* ATBProgressBar = NewObject<UProgressBar>(this);

	//EnemyBarBox ����
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
	//����
	HPProgressBar->SetPercent(1);
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);
	//���
	ATBProgressBar->SetPercent(0);
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::LeftToRight);



	//EnemyPortraitBox ����
	UOverlay* PortraitBox = NewObject<UOverlay>(this);
	UBorder* PortraitBorder = NewObject<UBorder>(this);
	UImage* Portrait = NewObject<UImage>(this);
	EnemyPortraitBox->AddChild(PortraitBox);

	PortraitBox->AddChild(PortraitBorder);
	PortraitBorder->AddChild(Portrait);

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
	//EnemyPortraitBox
	UTextBlock* LevelText = NewObject<UTextBlock>(this);
	EnemyLevelBox->AddChild(LevelText);
	{
		TArray<UPanelSlot*> Slots = EnemyLevelBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		int32 Level = InEnemyPawn->StatusComponent->GetSpeciesInfo()->Level;

		// "Level : ~" 형식의 텍스트 생성
		FString LevelTextString = FString::Printf(TEXT("Level : %d"), Level);


		LevelText->SetText(FText::FromString(LevelTextString));
	}
	UImage* AttributeImage = NewObject<UImage>(this);
	EnemyAttributeBox->AddChild(AttributeImage);
	{
		TArray<UPanelSlot*> Slots = EnemyAttributeBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = AttributeImage->GetBrush();

		BrushCopy.SetImageSize(FVector2D(30, 30.f));

		AttributeImage->SetBrush(BrushCopy);
		switch (InEnemyPawn->StatusComponent->GetSpeciesInfo()->Attribute)
		{
		case EAttribute::Data:
			AttributeImage->SetBrushFromTexture(DataTexture);
			break;
		case EAttribute::Vaccine:
			AttributeImage->SetBrushFromTexture(VaccineTexture);
			break;
		case EAttribute::Virus:
			AttributeImage->SetBrushFromTexture(VirusTexture);
			break;
		default:
			break;
		}
	}

	//ATBBar�� �߰�
	USlider* ATBSlider = NewObject<USlider>(this);
	ATBBarBox->AddChild(ATBSlider);
	{
		TArray<UPanelSlot*> Slots = ATBBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSliderStyle SliderStyle;
		FSlateBrush SlateBrush;
		SlateBrush.SetImageSize(FVector2D(100.f, 100.f));
		SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
		SlateBrush.SetResourceObject(InEnemyPawn->GetPortrait());
		FSlateBrushOutlineSettings OutlineSettings(30.f, FSlateColor(FColor(1.f, 0.f, 0.f, 1.f)), 5.f);
		SlateBrush.OutlineSettings = OutlineSettings;
		SliderStyle.SetDisabledThumbImage(SlateBrush);
		SliderStyle.SetNormalThumbImage(SlateBrush);
		ATBSlider->SetWidgetStyle(SliderStyle);
		ATBSlider->SetSliderBarColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
	}
	//����ü ����
	FPawnUIElements PawnUIElements;

	PawnUIElements.SliderBar = ATBSlider;

	TWeakObjectPtr<UOverlay> WeakProgressBarBoxPtr;
	WeakProgressBarBoxPtr = ProgressBarBox;

	PawnUIElements.ProgressBarBox = WeakProgressBarBoxPtr;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;

	TWeakObjectPtr<UOverlay> WeakPortraitBoxPtr;
	WeakPortraitBoxPtr = PortraitBox;

	PawnUIElements.PortraitBox = WeakPortraitBoxPtr;
	PawnUIElements.Portrait = Portrait;

	PawnUIElements.LevelText = LevelText;
	PawnUIElements.AttributeImage = AttributeImage;

	EnemyUI.Add(InEnemyPawn, PawnUIElements);
}



void UATBBattleUserWidget::AddFriendlyUI(ABasePawn* InFriendlyPawn)
{
	if (!InFriendlyPawn) { return; }

	InFriendlyPawn->OnChangedATBBar.AddDynamic(this, &ThisClass::OnATBBarUpdate);
	InFriendlyPawn->OnChangedHPBar.AddDynamic(this, &ThisClass::OnHPBarUpdate);

	UOverlay* ProgressBarBox = NewObject<UOverlay>(this);
	UImage* Image = NewObject<UImage>(this);
	UVerticalBox* VerticalBox = NewObject<UVerticalBox>(this);
	UOverlay* HPOverlay = NewObject<UOverlay>(this);
	UOverlay* ATBOverlay = NewObject<UOverlay>(this);
	UProgressBar* HPProgressBar = NewObject<UProgressBar>(this);
	UProgressBar* ATBProgressBar = NewObject<UProgressBar>(this);

	//FriendlyBarBox ����
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
	//����
	HPProgressBar->SetPercent(1);
	HPProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	HPProgressBar->SetBarFillType(EProgressBarFillType::RightToLeft);
	//���
	ATBProgressBar->SetPercent(0);
	ATBProgressBar->SetFillColorAndOpacity(FLinearColor(1.f, 1.f, 0.f));
	ATBProgressBar->SetBarFillType(EProgressBarFillType::RightToLeft);

	//FriendlyPortraitBox ����
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

	UTextBlock* LevelText = NewObject<UTextBlock>(this);
	FriendlyLevelBox->AddChild(LevelText);
	{
		TArray<UPanelSlot*> Slots = FriendlyLevelBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		int32 Level = InFriendlyPawn->StatusComponent->GetSpeciesInfo()->Level;

		// "Level : ~" 형식의 텍스트 생성
		FString LevelTextString = FString::Printf(TEXT("Level : %d"), Level);


		LevelText->SetText(FText::FromString(LevelTextString));
		LevelText->SetJustification(ETextJustify::Right);
	}

	UImage* AttributeImage = NewObject<UImage>(this);
	FriendlyAttributeBox->AddChild(AttributeImage);
	{
		TArray<UPanelSlot*> Slots = FriendlyAttributeBox->GetSlots();
		for (auto& VerticalBoxSlots : Slots)
		{
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(VerticalBoxSlots);

			VerticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			VerticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			FSlateChildSize Size(ESlateSizeRule::Fill);
			VerticalBoxSlot->SetSize(Size);

			VerticalBoxSlot->SynchronizeProperties();
		}
		FSlateBrush BrushCopy = AttributeImage->GetBrush();

		BrushCopy.SetImageSize(FVector2D(30, 30.f));

		AttributeImage->SetBrush(BrushCopy);
		switch (InFriendlyPawn->StatusComponent->GetSpeciesInfo()->Attribute)
		{
		case EAttribute::Data:
			AttributeImage->SetBrushFromTexture(DataTexture);
			break;
		case EAttribute::Vaccine:
			AttributeImage->SetBrushFromTexture(VaccineTexture);
			break;
		case EAttribute::Virus:
			AttributeImage->SetBrushFromTexture(VirusTexture);
			break;
		default:
			break;
		}
	}

	USlider* ATBSlider = NewObject<USlider>(this);
	ATBBarBox->AddChild(ATBSlider);
	{
		TArray<UPanelSlot*> Slots = ATBBarBox->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);
			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
		FSliderStyle SliderStyle;
		FSlateBrush SlateBrush;
		SlateBrush.SetImageSize(FVector2D(100.f, 100.f));
		SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
		SlateBrush.SetResourceObject(InFriendlyPawn->GetPortrait());
		FSlateBrushOutlineSettings OutlineSettings(30.f, FSlateColor(FColor(0.f, 0.f, 1.f, 1.f)), 5.f);
		SlateBrush.OutlineSettings = OutlineSettings;
		SliderStyle.SetDisabledThumbImage(SlateBrush);
		SliderStyle.SetNormalThumbImage(SlateBrush);
		ATBSlider->SetWidgetStyle(SliderStyle);
		ATBSlider->SetSliderBarColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
		ATBSlider->SetLocked(true);
	}
	//����ü ����
	FPawnUIElements PawnUIElements;

	PawnUIElements.SliderBar = ATBSlider;

	TWeakObjectPtr<UOverlay> WeakProgressBarBoxPtr;
	WeakProgressBarBoxPtr = ProgressBarBox;

	PawnUIElements.ProgressBarBox = WeakProgressBarBoxPtr;
	PawnUIElements.ATBProgressBar = ATBProgressBar;
	PawnUIElements.HPProgressBar = HPProgressBar;

	TWeakObjectPtr<UOverlay> WeakPortraitBoxPtr;
	WeakPortraitBoxPtr = PortraitBox;

	PawnUIElements.PortraitBox = WeakPortraitBoxPtr;
	PawnUIElements.Portrait = Portrait;

	PawnUIElements.LevelText = LevelText;
	PawnUIElements.AttributeImage = AttributeImage;

	FriendlyUI.Add(InFriendlyPawn, PawnUIElements);
}

void UATBBattleUserWidget::RemovePawnUI(ABasePawn* DeadPawn)
{
	// NewPawn ������ ȣ�� 
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
		// UI ��� ���� ó��
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

			if (UIElements->SliderBar.IsValid())
			{
				UIElements->SliderBar->RemoveFromParent();
			}

			if (UIElements->LevelText.IsValid())
			{
				UIElements->LevelText->RemoveFromParent();
			}

			if (UIElements->AttributeImage.IsValid())
			{
				UIElements->AttributeImage->RemoveFromParent();
			}
		}
		// EnemyUI���� ����
		EnemyUI.Remove(DeadPawn);
	}
}

void UATBBattleUserWidget::RemoveFriendlyUI(ABasePawn* DeadPawn)
{
	if (DeadPawn && FriendlyUI.Contains(DeadPawn))
	{
		// UI ��� ���� ó��
		FPawnUIElements* UIElements = FriendlyUI.Find(DeadPawn);
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

			if (UIElements->SliderBar.IsValid())
			{
				UIElements->SliderBar->RemoveFromParent();
			}

			if (UIElements->LevelText.IsValid())
			{
				UIElements->LevelText->RemoveFromParent();
			}

			if (UIElements->AttributeImage.IsValid())
			{
				UIElements->AttributeImage->RemoveFromParent();
			}
		}
		// FriendlyUI���� ����
		FriendlyUI.Remove(DeadPawn);
	}
}

void UATBBattleUserWidget::OnUpdateUI(ABasePawn* UpdatePawn)
{

	if (UpdatePawn && FriendlyUI.Contains(UpdatePawn))
	{

		FPawnUIElements* UIElements = FriendlyUI.Find(UpdatePawn);
		if (UIElements)
		{
			if (UIElements->Portrait.IsValid())
			{
				UIElements->Portrait->SetBrushFromTexture(UpdatePawn->GetPortrait());
				FSliderStyle SliderStyle;
				FSlateBrush SlateBrush;
				SlateBrush.SetImageSize(FVector2D(100.f, 100.f));
				SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
				SlateBrush.SetResourceObject(UpdatePawn->GetPortrait());
				FSlateBrushOutlineSettings OutlineSettings(30.f, FSlateColor(FColor(0.f, 0.f, 1.f, 1.f)), 5.f);
				SlateBrush.OutlineSettings = OutlineSettings;
				SliderStyle.SetDisabledThumbImage(SlateBrush);
				SliderStyle.SetNormalThumbImage(SlateBrush);
				UIElements->SliderBar->SetWidgetStyle(SliderStyle);
			}
			if (UIElements->LevelText.IsValid())
			{
				int32 Level = UpdatePawn->StatusComponent->GetSpeciesInfo()->Level;

				// "Level : ~" 형식의 텍스트 생성
				FString LevelTextString = FString::Printf(TEXT("Level : %d"), Level);


				UIElements->LevelText->SetText(FText::FromString(LevelTextString));
				UIElements->LevelText->SetJustification(ETextJustify::Right);
			}
			if (UIElements->AttributeImage.IsValid())
			{
				FSlateBrush BrushCopy = UIElements->AttributeImage->GetBrush();

				BrushCopy.SetImageSize(FVector2D(30, 30.f));

				UIElements->AttributeImage->SetBrush(BrushCopy);
				switch (UpdatePawn->StatusComponent->GetSpeciesInfo()->Attribute)
				{
				case EAttribute::Data:
					UIElements->AttributeImage->SetBrushFromTexture(DataTexture);
					break;
				case EAttribute::Vaccine:
					UIElements->AttributeImage->SetBrushFromTexture(VaccineTexture);
					break;
				case EAttribute::Virus:
					UIElements->AttributeImage->SetBrushFromTexture(VirusTexture);
					break;
				default:
					break;
				}
			}
		}
	}
	else if (UpdatePawn && EnemyUI.Contains(UpdatePawn))
	{
		FPawnUIElements* UIElements = EnemyUI.Find(UpdatePawn);
		if (UIElements)
		{
			if (UIElements->Portrait.IsValid())
			{
				UIElements->Portrait->SetBrushFromTexture(UpdatePawn->GetPortrait());
				FSliderStyle SliderStyle;
				FSlateBrush SlateBrush;
				SlateBrush.SetImageSize(FVector2D(100.f, 100.f));
				SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
				SlateBrush.SetResourceObject(UpdatePawn->GetPortrait());
				FSlateBrushOutlineSettings OutlineSettings(30.f, FSlateColor(FColor(0.f, 0.f, 1.f, 1.f)), 5.f);
				SlateBrush.OutlineSettings = OutlineSettings;
				SliderStyle.SetDisabledThumbImage(SlateBrush);
				SliderStyle.SetNormalThumbImage(SlateBrush);
				UIElements->SliderBar->SetWidgetStyle(SliderStyle);
			}
			if (UIElements->LevelText.IsValid())
			{
				int32 Level = UpdatePawn->StatusComponent->GetSpeciesInfo()->Level;

				// "Level : ~" 형식의 텍스트 생성
				FString LevelTextString = FString::Printf(TEXT("Level : %d"), Level);


				UIElements->LevelText->SetText(FText::FromString(LevelTextString));
				UIElements->LevelText->SetJustification(ETextJustify::Right);
			}
			if (UIElements->AttributeImage.IsValid())
			{
				FSlateBrush BrushCopy = UIElements->AttributeImage->GetBrush();

				BrushCopy.SetImageSize(FVector2D(30, 30.f));

				UIElements->AttributeImage->SetBrush(BrushCopy);
				switch (UpdatePawn->StatusComponent->GetSpeciesInfo()->Attribute)
				{
				case EAttribute::Data:
					UIElements->AttributeImage->SetBrushFromTexture(DataTexture);
					break;
				case EAttribute::Vaccine:
					UIElements->AttributeImage->SetBrushFromTexture(VaccineTexture);
					break;
				case EAttribute::Virus:
					UIElements->AttributeImage->SetBrushFromTexture(VirusTexture);
					break;
				default:
					break;
				}
			}
		}
	}
}


void UATBBattleUserWidget::OnHPBarUpdate(ABasePawn* InPawn, float InPercent)
{
	if (InPawn && FriendlyUI.Contains(InPawn))
	{
		FPawnUIElements* UIElements = FriendlyUI.Find(InPawn);
		if (UIElements)
		{
			if (UIElements->HPProgressBar.IsValid())
			{
				UIElements->HPProgressBar->SetPercent(InPercent);
			}
		}
	}
	else if (InPawn && EnemyUI.Contains(InPawn))
	{
		FPawnUIElements* UIElements = EnemyUI.Find(InPawn);
		if (UIElements)
		{
			if (UIElements->HPProgressBar.IsValid())
			{
				UIElements->HPProgressBar->SetPercent(InPercent);
			}
		}
	}
}

void UATBBattleUserWidget::OnATBBarUpdate(ABasePawn* InPawn, float InPercent)
{
	if (InPawn && FriendlyUI.Contains(InPawn))
	{
		FPawnUIElements* UIElements = FriendlyUI.Find(InPawn);
		if (UIElements)
		{
			if (UIElements->ATBProgressBar.IsValid())
			{
				UIElements->ATBProgressBar->SetPercent(InPercent);
				UIElements->SliderBar->SetValue(InPercent);
			}
		}
	}
	else if (InPawn && EnemyUI.Contains(InPawn))
	{
		FPawnUIElements* UIElements = EnemyUI.Find(InPawn);
		if (UIElements)
		{
			if (UIElements->ATBProgressBar.IsValid())
			{
				UIElements->ATBProgressBar->SetPercent(InPercent);
				UIElements->SliderBar->SetValue(InPercent);
			}
		}
	}
}
