// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimComponent.h"
#include "Subsystem/DataSubsystem.h"

// Sets default values for this component's properties
UAnimComponent::UAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
}


// Called when the game starts
void UAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UAnimComponent::SetData(ESpecies InSpecies)
{
	AnimData = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>()->GetDataTableRow<FAnimMontageTableRow>(EDataTableType::Animation, InSpecies);
}

