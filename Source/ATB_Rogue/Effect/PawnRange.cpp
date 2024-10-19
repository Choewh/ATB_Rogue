// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/PawnRange.h"
#include "PawnRange.h"

APawnRange::APawnRange()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	{
		StaticMeshComponent->SetCollisionProfileName(TEXT("EnemySeach"));
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	}
}

void APawnRange::SetData(const FDataTableRowHandle& EffectDataTableRowHandle)
{
	if (EffectDataTableRowHandle.IsNull()) { return; }
	{
		FEffectTableRow* Data = EffectDataTableRowHandle.GetRow<FEffectTableRow>(TEXT("RangeEffect"));
		if (!Data) { ensure(false); return; }

		StaticMeshComponent->SetStaticMesh(Data->RangeMesh);
	}
}


void APawnRange::BeginPlay()
{
}

void APawnRange::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
