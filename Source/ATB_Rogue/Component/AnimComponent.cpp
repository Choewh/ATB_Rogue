// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AnimComponent.h"
#include "AnimComponent.h"

// Sets default values for this component's properties
UAnimComponent::UAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UDataTable> AnimDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/AnimTableRow.AnimTableRow'"));
	if (AnimDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
		AnimDataTable = AnimDataObject.Object;
	}
}


// Called when the game starts
void UAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAnimComponent::SetData(ESpecies InSpecies)
{
	TArray<FAnimMontageTableRow*> AnimTable_Array;
	AnimDataTable->GetAllRows<FAnimMontageTableRow>("", AnimTable_Array);

	for (auto& AnimTable : AnimTable_Array)
	{
		if (AnimTable->Species == InSpecies)
		{
			AnimData = AnimTable;
		}
	}
}

