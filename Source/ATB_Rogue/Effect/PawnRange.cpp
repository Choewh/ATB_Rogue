// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/PawnRange.h"
#include "PawnRange.h"

APawnRange::APawnRange()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DecalMeshComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalMeshComponent"));
	DecalMeshComponent->SetupAttachment(RootComponent);
	{
		AActor* temp = GetOwner();
	}
}

void APawnRange::SetData(FEffectTableRow& EffectData)
{
	DecalMeshComponent->SetMaterial(0, EffectData.RangeDecalMaterial);
	DecalMeshComponent->SetRelativeTransform(EffectData.RangeDecalTransform);
	DecalMeshComponent->DecalSize = FVector(20.f, 100.f, 100.f);
}

void APawnRange::HideEffect()
{
	ReturnToPool();
}


void APawnRange::BeginPlay()
{
}

//void APawnRange::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//}
