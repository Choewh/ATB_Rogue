// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/PawnRange.h"
#include "PawnRange.h"

APawnRange::APawnRange()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DecalMeshComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalMeshComponent"));
	DecalMeshComponent->SetupAttachment(RootComponent);
}

void APawnRange::SetData(UMaterial* DecalMaterial)
{
	DecalMeshComponent->SetMaterial(0,DecalMaterial);
	DecalMeshComponent->DecalSize = FVector(100.f, 100.f, 1.f);
}


void APawnRange::BeginPlay()
{
}

//void APawnRange::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//}
