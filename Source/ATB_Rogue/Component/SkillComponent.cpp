// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillComponent.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/SkillTable.SkillTable'"));
	if (SkillDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
		SkillDataTable = SkillDataObject.Object;
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
	TArray<FSkillTableRow*> SkillTable_Array;
	SkillDataTable->GetAllRows<FSkillTableRow>("", SkillTable_Array);

	for (auto& SkillTable : SkillTable_Array)
	{
		if (SkillTable->Species == InSpecies)
		{
			SkillData = SkillTable;
		}
	}
}

float USkillComponent::GetSkillRange(ESkills InSkill)
{
	if (SkillData) { return -1.f; }
	
	switch (InSkill)
	{
	case ESkills::FirstSkill:
		return SkillData->Skill1_Range;
	case ESkills::SecondSkill:
		return SkillData->Skill2_Range;
	case ESkills::ThirdSkill:
		return SkillData->Skill3_Range;
	default:
		return -1.f;
	}
	
}

