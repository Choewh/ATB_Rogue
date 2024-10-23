// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EffectComponent.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "EffectComponent.h"


UEffectComponent::UEffectComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> EffectDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/EffectTableRow.EffectTableRow'"));
	if (EffectDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("EffectData Succeeded"));
		EffectDataTable = EffectDataObject.Object;
	}
}


void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UEffectComponent::SetData(ESpecies InSpecies)
{
	TArray<FEffectTableRow*> EffectTable_Array;
	EffectDataTable->GetAllRows<FEffectTableRow>("", EffectTable_Array);

	for (auto& EffectTable : EffectTable_Array)
	{
		if (EffectTable->Species == InSpecies)
		{
			EffectData = EffectTable;
		}
	}
}

void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEffectComponent::ViewMoveRange(FVector PawnLocation,float MoveRange)
{
	float Scale = (MoveRange) / 100;
	FTransform NewTransform(FRotator::ZeroRotator, PawnLocation, FVector(0.1f, Scale, Scale));
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->SpawnRangeEffect(NewTransform,*EffectData);
}

void UEffectComponent::DeViewMoveRange()
{
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
}

