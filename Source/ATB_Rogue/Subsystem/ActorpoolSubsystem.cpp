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
	APawnRange* DeSpawnPawnRange = PawnRange.GetPoolingTopActor();
	if (!DeSpawnPawnRange) { return; }
	DeSpawnPawnRange->ReturnToPool();
}
//
//void UActorpoolSubsystem::DeSpawnRangeEffect(APooledActor* DeSpawnActor)
//{
//	APawnRange* DeSpawnPawnRange =	Cast<APawnRange>(DeSpawnActor);
//	if (!DeSpawnPawnRange) { return; }
//	DeSpawnPawnRange->ReturnToPool();
//}

void UActorpoolSubsystem::SpawnViewUI(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle)
{
}

void UActorpoolSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	PawnRange.InitializePool(&InWorld, 1);
}
