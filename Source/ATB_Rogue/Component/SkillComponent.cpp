// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillComponent.h"
#include "Subsystem/DataSubsystem.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
}



void USkillComponent::SetData(ESpecies InSpecies)
{
	SkillData = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>()->GetDataTableRow<FSpeciesSkillTableRow>(EDataTableType::Skill, InSpecies);
	
	if(!SkillData) { ensure(false); return; }

	FSkillTableRow* FirstData = SkillData->FirstSkill.GetRow<FSkillTableRow>(TEXT("FirstSkill"));
	if(!FirstData) { ensure(false); return; }
	FirstSkillData = FirstData;

	FSkillTableRow* SecondData = SkillData->SecondSkill.GetRow<FSkillTableRow>(TEXT("SecondSkill"));
	if (!SecondData) { ensure(false); return; }
	SecondSkillData = SecondData;

	if (SkillData->Skill_3)
	{
		FSkillTableRow* ThirdData = SkillData->ThirdSkill.GetRow<FSkillTableRow>(TEXT("ThirdSkill"));
		if (!ThirdData) { ensure(false); return; }
		ThirdSkillData = ThirdData;
	}
}

FSkillTableRow* USkillComponent::GetSkillData(ESkills InSkill)
{
	switch (InSkill)
	{
	case ESkills::FirstSkill:
		if(!FirstSkillData) { ensure(false); return nullptr ;}
		return FirstSkillData;
	case ESkills::SecondSkill:
		if(!SecondSkillData) { ensure(false); return nullptr;}
		return SecondSkillData;
	case ESkills::ThirdSkill:
		if (!ThirdSkillData) { ensure(false); return nullptr; }
		return ThirdSkillData;
	default:
		return nullptr;
	}
}