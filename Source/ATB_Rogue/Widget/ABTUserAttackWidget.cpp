// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ABTUserAttackWidget.h"
#include "Pawn/BasePawn.h"
#include "ABTUserAttackWidget.h"
void UABTUserAttackWidget::NativeOnInitialized()
{
}

void UABTUserAttackWidget::NativePreConstruct()
{
}

void UABTUserAttackWidget::NativeConstruct()
{
	Init();
}

void UABTUserAttackWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UABTUserAttackWidget::Init()
{
	SetImage();
}

void UABTUserAttackWidget::ShowSkillRange(ESkills UseSkill)
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

void UABTUserAttackWidget::SetImage()
{
	ABasePawn* BasePawn =GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn();
	FirstSkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::FirstSkill)->Skill_Icon);
	SecondSkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::SecondSkill)->Skill_Icon);
	if (BasePawn->SkillComponent->SpeciesSkillData->Skill_3)
	{
		ThirdSkillImage->SetBrushFromTexture(BasePawn->SkillComponent->GetSkillData(ESkills::ThirdSkill)->Skill_Icon);
	}
	else
	{
		//보이지 않게하기 없다는 이미지 띄워주기ㅇㅇ 이게 나을듯 그냥 설정안해주고 디폴트값을 없다 ㄱ
	}
}
