// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EffectComponent.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "Subsystem/DataSubsystem.h"

#include "EffectComponent.h"


UEffectComponent::UEffectComponent()
{
}


void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEffectComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	PawnGruopEffect->HideEffect();
}

void UEffectComponent::SetData(ESpecies InSpecies)
{
	EffectData = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>()->GetEffect();

	if (!PawnGruopEffect)
	{
		PawnGruopEffect = GetWorld()->GetSubsystem<UActorpoolSubsystem>()->SpawnGroupEffect(GetOwner(), *EffectData);
	}
}

void UEffectComponent::ShowRange(FVector PawnLocation, float MoveRange)
{
	float Scale = (MoveRange) / 100;
	FTransform NewTransform(FRotator::ZeroRotator, PawnLocation, FVector(100.f, Scale, Scale));
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->SpawnRangeEffect(NewTransform, *EffectData);
}

void UEffectComponent::HideRange()
{
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
}

