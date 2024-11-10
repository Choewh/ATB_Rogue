// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ATBUserAttackWidget.h"
#include "Pawn/BasePawn.h"
#include "Widget/USelectableCell.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "ATBUserAttackWidget.h"
void UATBUserAttackWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UTexture2D* SkillBGObject = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Resource/UI/Texture/Battle/BattleDigimon_Portrait/Battle_Digimon_Skill_BG.Battle_Digimon_Skill_BG'"));
	check(SkillBGObject);
	SkillBG = SkillBGObject;

}

void UATBUserAttackWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Init();
}

void UATBUserAttackWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetSubsystem<UBattleSubsystem>()->RemoveWidget.AddDynamic(this, &ThisClass::FinishTurn);
}

void UATBUserAttackWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UATBUserAttackWidget::Init()
{
	CreateSkillUI();
}

void UATBUserAttackWidget::ShowSkillRange(ESkills UseSkill)
{
	ABasePawn* BasePawn = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn();
	switch (UseSkill)
	{
	case ESkills::None:
		BasePawn->EffectComponent->HideRange();
		break;
	case ESkills::FirstSkill:
		BasePawn->EffectComponent->HideRange();
		BasePawn->EffectComponent->ShowRange(BasePawn->GetActorLocation(),BasePawn->SkillComponent->FirstSkillData->Skill_Range);
		break;
	case ESkills::SecondSkill:
		BasePawn->EffectComponent->HideRange();
		BasePawn->EffectComponent->ShowRange(BasePawn->GetActorLocation(), BasePawn->SkillComponent->SecondSkillData->Skill_Range);
		break;
	case ESkills::ThirdSkill:
		if (!BasePawn->SkillComponent->SpeciesSkillData->Skill_3) { return; }
		
		BasePawn->EffectComponent->HideRange();
		BasePawn->EffectComponent->ShowRange(BasePawn->GetActorLocation(), BasePawn->SkillComponent->ThirdSkillData->Skill_Range);
		
		break;
	default:
		BasePawn->EffectComponent->HideRange();
		break;
	}
}

void UATBUserAttackWidget::FinishTurn()
{
	RemoveFromParent();
}

void UATBUserAttackWidget::CreateSkillUI()
{
	if (!BattleSubsystem) { return; }

	ABasePawn* BasePawn = BattleSubsystem->GetActionPawn();

	if (!BasePawn) { return; }

	for (uint8 i = 1; i <= 3; i++)
	{
		if (i == 3 && !BasePawn->SkillComponent->SpeciesSkillData->Skill_3) { break; }
		UOverlay* SkillOverlay = NewObject<UOverlay>(this);
		UBorder* SkillBorder = NewObject<UBorder>(this);
		UImage* SkillImage = NewObject<UImage>(this);
		UButton* SkillButton = NewObject<UButton>(this);

		SkillHorizontalBox->AddChild(SkillBorder);
		SkillBorder->AddChild(SkillOverlay);
		SkillOverlay->AddChild(SkillImage);
		SkillOverlay->AddChild(SkillButton);

		//배경투명하게설정
		SkillButton->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 0.f));

		{
			TArray<UPanelSlot*> Slots = SkillHorizontalBox->GetSlots();
			for (auto& HorizontalBoxSlots : Slots)
			{
				UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(HorizontalBoxSlots);

				HorizontalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				HorizontalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				FSlateChildSize Size(ESlateSizeRule::Fill);
				HorizontalBoxSlot->SetSize(Size);


				HorizontalBoxSlot->SynchronizeProperties();
			}
			SkillBorder->SetBrushFromTexture(SkillBG);

		}
		{
			TArray<UPanelSlot*> Slots = SkillOverlay->GetSlots();
			for (auto& OverlaySlots : Slots)
			{
				UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

				OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
				OverlaySlot->SynchronizeProperties();
			}
		}
		FSlateBrush BrushCopy = SkillImage->GetBrush();

		BrushCopy.SetImageSize(FVector2D(128.f, 128.f));
		BrushCopy.DrawAs = ESlateBrushDrawType::RoundedBox;

		SkillImage->SetBrush(BrushCopy);
		switch (i)
		{
		case static_cast<uint8>(ESkills::FirstSkill):
			SkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::FirstSkill)->Skill_Icon);
			FirstSkillCell = SkillButton;
			break;
		case static_cast<uint8>(ESkills::SecondSkill):
			SkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::SecondSkill)->Skill_Icon);
			SecondSkillCell = SkillButton;
			break;
		case static_cast<uint8>(ESkills::ThirdSkill):
			
			SkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::ThirdSkill)->Skill_Icon);
			ThirdSkillCell = SkillButton;
			break;
		default:
			break;
		}
	}
}
