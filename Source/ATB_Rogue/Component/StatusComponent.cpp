// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatusComponent.h"


// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
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
		Stage = StatData->Stage;
		Attribute = StatData->Attribute;
		HP = StatData->HP;
		ATK = StatData->ATK;
		DEF = StatData->DEF;
		SPATK = StatData->SPATK;
		SPDEF = StatData->SPDEF;
		SPD = StatData->SPD;
		ACC = StatData->ACC;
		EVA = StatData->EVA;
		MoveRange = StatData->MoveRange;
	}
}

// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UStatusComponent::GetStat(EStat StatName)
{
	switch (StatName)
	{
	case EStat::HP:
		return HP;    // HP�� ���� �� ��ȯ
	case EStat::ATK:
		return ATK;   // ATK�� ���� �� ��ȯ
	case EStat::DEF:
		return DEF;   // DEF�� ���� �� ��ȯ
	case EStat::SPATK:
		return SPATK; // SPATK�� ���� �� ��ȯ
	case EStat::SPDEF:
		return SPDEF; // SPDEF�� ���� �� ��ȯ
	case EStat::SPD:
		return SPD;   // SPD�� ���� �� ��ȯ
	case EStat::ACC:
		return ACC;   // ACC�� ���� �� ��ȯ
	case EStat::EVA:
		return EVA;   // EVA�� ���� �� ��ȯ
	default:
		return -1.f;  // ������ -1.f
	}
}

