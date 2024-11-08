// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatusComponent.h"
#include "Engine/DamageEvents.h"
#include "Pawn/BasePawn.h"
#include "Misc/AllDamageType.h"


	
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

	SpeciesInfo = MakeShared<FSpeciesInfo>();
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
			break;
		}
	}

	if (!StatData) { UE_LOG(LogTemp, Log, TEXT("StatusComponent is Not Find")); return; }

	{
		TSharedPtr<FSpeciesInfo> NewSpeciesInfo = MakeShared<FSpeciesInfo>();

		NewSpeciesInfo.Get()->Level = SpeciesInfo.Get()->Level;
		NewSpeciesInfo.Get()->Species = InSpecies;
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
		// 베이스 스탯
		// 이후 추가
		SpeciesInfo = NewSpeciesInfo;
	}
}

float UStatusComponent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Damage;

	ABasePawn* DamageCauserPawn = Cast<ABasePawn>(DamageCauser);

	float Mod1 =  AffinityCalcu(DamageCauserPawn->StatusComponent->GetSpeciesInfo()->Attribute,SpeciesInfo.Get()->Attribute);

	if (DamageEvent.DamageTypeClass == USpecialType::StaticClass())
	{
		NewDamage = (NewDamage / SpeciesInfo.Get()->SPDEF + 2) * GetRand() / 100.f * Mod1;
	}
	else if (DamageEvent.DamageTypeClass == UMeleeType::StaticClass())
	{
		NewDamage = (NewDamage / SpeciesInfo.Get()->DEF + 2) * GetRand() / 100.f * Mod1;
	}
	UE_LOG(LogTemp, Warning, TEXT("ResultDamage : %f"), NewDamage);
	return NewDamage;
}

float UStatusComponent::AffinityCalcu(EAttribute CauserAttribute, EAttribute thisAttribute)
{
	float temp = AffinityTable[static_cast<uint8>(CauserAttribute)][static_cast<uint8>(thisAttribute)];
	return AffinityTable[static_cast<uint8>(CauserAttribute)][static_cast<uint8>(thisAttribute)];
}
