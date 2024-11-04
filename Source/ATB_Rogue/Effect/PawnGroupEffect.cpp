// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/PawnGroupEffect.h"
#include "Pawn/BasePawn.h"
#include "PawnGroupEffect.h"

APawnGroupEffect::APawnGroupEffect()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DecalMeshComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalMeshComponent"));
	DecalMeshComponent->SetupAttachment(RootComponent);
}

void APawnGroupEffect::BeginPlay()
{
	Super::BeginPlay();
}

void APawnGroupEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!OwningPawn) { return; }
	FVector NewVector = OwningPawn->GetActorLocation();
	NewVector.Z = 0.f;
	SetActorLocation(NewVector);
}

void APawnGroupEffect::SetData(FEffectTableRow& EffectData)
{
	if(!EffectData.GroupDecalMaterial) { return; }

	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(EffectData.GroupDecalMaterial, this);
	DecalMeshComponent->SetMaterial(0, DynamicMaterial);
	DecalMeshComponent->SetRelativeTransform(EffectData.GroupDecalTransform);
	DecalMeshComponent->DecalSize = FVector(100.f, 100.f, 100.f);
	if (!OwningPawn) { return; }

	ABasePawn* OwnerPawn = Cast<ABasePawn>(OwningPawn);

	if (OwnerPawn->PawnGroup == EPawnGroup::Enemy)
	{
		DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), FLinearColor::Red);
	}
}

void APawnGroupEffect::SetOwningPawn(AActor* InOwner)
{
	OwningPawn = InOwner;
}

void APawnGroupEffect::HideEffect()
{
	OwningPawn = nullptr;
	ReturnToPool();
}

