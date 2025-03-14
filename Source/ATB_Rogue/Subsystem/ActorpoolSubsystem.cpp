// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/ActorpoolSubsystem.h"
#include "ActorpoolSubsystem.h"

void UActorpoolSubsystem::SpawnEffect(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle)
{
}

void UActorpoolSubsystem::SpawnRangeEffect(const FTransform SpawnTransform,FEffectTableRow& EffectTableRow)
{
	APawnRange* NewPawnRange = PawnRange.GetActorFromPool();
	NewPawnRange->SetData(EffectTableRow);
	NewPawnRange->SetActorTransform(SpawnTransform);
	//LifeSpanExpired() , ������Ǯ
}
void UActorpoolSubsystem::DeSpawnRangeEffect()
{
	APawnRange* DeSpawnPawnRange = PawnRange.GetPoolingPopActor();
	if (!DeSpawnPawnRange) { return; }
	DeSpawnPawnRange->HideEffect();
}
APawnGroupEffect* UActorpoolSubsystem::SpawnGroupEffect(AActor* Owner, FEffectTableRow& EffectTableRow)
{
	APawnGroupEffect* NewPawnGroup = PawnGroupEffect.GetActorFromPool();
	NewPawnGroup->SetOwningPawn(Owner);
	NewPawnGroup->SetData(EffectTableRow);
	return NewPawnGroup;
}
void UActorpoolSubsystem::DeSpawnGroupEffect()
{
	APawnGroupEffect* DeNewPawnGroup = PawnGroupEffect.GetPoolingPopActor();
	if (!DeNewPawnGroup) { return; }
	DeNewPawnGroup->HideEffect();
}
ACursorEffect* UActorpoolSubsystem::CursorEffectSpawn(const FVector SpawnTransform)
{
	ACursorEffect* NewCursorEffect = CursorEffect.GetActorFromPool();
	NewCursorEffect->SetActorLocation(SpawnTransform);
	NewCursorEffect->PlayEffect();
	return NewCursorEffect;
}

void UActorpoolSubsystem::SpawnViewUI(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle)
{
}

void UActorpoolSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	PawnRange.InitializePool(&InWorld, 1);
	PawnGroupEffect.InitializePool(&InWorld, 10);
	CursorEffect.InitializePool(&InWorld, 1);
}
