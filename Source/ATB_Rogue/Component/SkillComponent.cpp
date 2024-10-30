// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillComponent.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> SpeciesSkillDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/SkillTable.SkillTable'"));
	if (SpeciesSkillDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
		SpeciesSkillDataTable = SpeciesSkillDataObject.Object;
	}
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillComponent::SetData(ESpecies InSpecies)
{
	TArray<FSpeciesSkillTableRow*> SpeciesSkillTableRow_Array;
	SpeciesSkillDataTable->GetAllRows<FSpeciesSkillTableRow>("", SpeciesSkillTableRow_Array);

	for (auto& SpeciesSkillTable : SpeciesSkillTableRow_Array)
	{
		if (SpeciesSkillTable->Species == InSpecies)
		{
			SpeciesSkillData = SpeciesSkillTable;
		}
	}
	FSkillTableRow* FirstData = SpeciesSkillData->FirstSkill.GetRow<FSkillTableRow>(TEXT("FirstSkill"));
	if(!FirstData) { ensure(false); return; }
	FirstSkillData = FirstData;
	FSkillTableRow* SecondData = SpeciesSkillData->FirstSkill.GetRow<FSkillTableRow>(TEXT("SecondSkill"));
	if (!SecondData) { ensure(false); return; }
	SecondSkillData = SecondData;
	FSkillTableRow* ThirdData = SpeciesSkillData->FirstSkill.GetRow<FSkillTableRow>(TEXT("ThirdSkill"));
	if (!ThirdData) { ensure(false); return; }
	ThirdSkillData = ThirdData;
}

float USkillComponent::GetSkillRange(ESkills InSkill)
{
	switch (InSkill)
	{
	case ESkills::FirstSkill:
		if(!FirstSkillData) { ensure(false); return-1.f;}
		return FirstSkillData->Skill_Range;
	case ESkills::SecondSkill:
		if(!SecondSkillData) { ensure(false); return-1.f;}
		return SecondSkillData->Skill_Range;
	case ESkills::ThirdSkill:
		if (!ThirdSkillData) { ensure(false); return-1.f; }
		return ThirdSkillData->Skill_Range;
	default:
		return -1.f;
	}
	
}

