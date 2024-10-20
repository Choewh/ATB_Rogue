// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EffectComponent.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "EffectComponent.h"


// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> EffectDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/EffectTableRow.EffectTableRow'"));
	if (EffectDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("EffectData Succeeded"));
		EffectDataTable = EffectDataObject.Object;
	}
	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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

// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEffectComponent::ViewMoveRange(FVector PawnLocation,float MoveRange)
{
	float Scale = (MoveRange) / 100;
	FTransform NewTransform(FRotator::ZeroRotator, PawnLocation, FVector(Scale, Scale, 0.1f));
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->SpawnRangeEffect(NewTransform,EffectData->MoveRangeMaterial);
}

void UEffectComponent::DeViewMoveRange()
{
}

