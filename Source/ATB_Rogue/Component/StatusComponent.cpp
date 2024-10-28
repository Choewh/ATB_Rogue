// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatusComponent.h"


// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> StatDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/StatTable.StatTable'"));
	if (StatDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
		StatDataTable = StatDataObject.Object;
	}
}



// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusComponent::SetData(ESpecies InSpecies)
{
	TArray<FStatTableRow*> StatTable_Array;
	StatDataTable->GetAllRows<FStatTableRow>("", StatTable_Array);

	for (auto& StatTable : StatTable_Array)
	{
		if (StatTable->Species == InSpecies)
		{
			StatData = StatTable;
		}
	}

	if (!StatData) { UE_LOG(LogTemp, Log, TEXT("StatusComponent is Not Find")); return; }

	{
		TUniquePtr<FSpeciesInfo> NewSpeciesInfo = MakeUnique<FSpeciesInfo>();
		NewSpeciesInfo.Get()->Stage = StatData->Stage;
		NewSpeciesInfo.Get()->Attribute = StatData->Attribute;
		NewSpeciesInfo.Get()->HP = StatData->HP;
		NewSpeciesInfo.Get()->ATK = StatData->ATK;
		NewSpeciesInfo.Get()->DEF = StatData->DEF;
		NewSpeciesInfo.Get()->SPATK = StatData->SPATK;
		NewSpeciesInfo.Get()->SPDEF = StatData->SPDEF;
		NewSpeciesInfo.Get()->SPD = StatData->SPD;
		NewSpeciesInfo.Get()->ACC = StatData->ACC;
		NewSpeciesInfo.Get()->EVA = StatData->EVA;
		NewSpeciesInfo.Get()->MoveRange = StatData->MoveRange;
		SetSpeciesInfo(MoveTemp(NewSpeciesInfo));
	}
}

float UStatusComponent::GetStat(EStat StatName)
{
	if(SpeciesInfo != nullptr)
	switch (StatName)
	{
	case EStat::HP:
		return SpeciesInfo.Get()->HP;    // HP�� ���� �� ��ȯ
	case EStat::ATK:
		return SpeciesInfo.Get()->ATK;   // ATK�� ���� �� ��ȯ
	case EStat::DEF:
		return SpeciesInfo.Get()->DEF;   // DEF�� ���� �� ��ȯ
	case EStat::SPATK:
		return SpeciesInfo.Get()->SPATK; // SPATK�� ���� �� ��ȯ
	case EStat::SPDEF:
		return SpeciesInfo.Get()->SPDEF; // SPDEF�� ���� �� ��ȯ
	case EStat::SPD:
		return SpeciesInfo.Get()->SPD;   // SPD�� ���� �� ��ȯ
	case EStat::ACC:
		return SpeciesInfo.Get()->ACC;   // ACC�� ���� �� ��ȯ
	case EStat::EVA:
		return SpeciesInfo.Get()->EVA;   // EVA�� ���� �� ��ȯ
	default:
		return -1.f;  // ������ -1.f
	}
	return -1.f;
}

TUniquePtr<FSpeciesInfo> UStatusComponent::GetSpeciesInfo()
{
	TUniquePtr<FSpeciesInfo> ResultSpeciesInfo = MakeUnique<FSpeciesInfo>();
	ResultSpeciesInfo.Get()->Stage = SpeciesInfo->Stage;
	ResultSpeciesInfo.Get()->Attribute = SpeciesInfo->Attribute;
	ResultSpeciesInfo.Get()->HP = SpeciesInfo->HP;
	ResultSpeciesInfo.Get()->ATK = SpeciesInfo->ATK;
	ResultSpeciesInfo.Get()->DEF = SpeciesInfo->DEF;
	ResultSpeciesInfo.Get()->SPATK = SpeciesInfo->SPATK;
	ResultSpeciesInfo.Get()->SPDEF = SpeciesInfo->SPDEF;
	ResultSpeciesInfo.Get()->SPD = SpeciesInfo->SPD;
	ResultSpeciesInfo.Get()->ACC = SpeciesInfo->ACC;
	ResultSpeciesInfo.Get()->EVA = SpeciesInfo->EVA;
	ResultSpeciesInfo.Get()->MoveRange = SpeciesInfo->MoveRange;

	return ResultSpeciesInfo;
}

