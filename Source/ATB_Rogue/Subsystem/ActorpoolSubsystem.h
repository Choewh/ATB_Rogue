// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Pawn/BasePawn.h"
#include "Misc/Actorpool.h"
#include "Effect/PawnRange.h"
#include "ActorpoolSubsystem.generated.h"

/**
 *
 */

UCLASS()
class ATB_ROGUE_API UActorpoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SpawnEffect(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);

	//이펙트 스폰 ㅇ
	void SpawnRangeEffect(const FTransform SpawnTransform, FEffectTableRow& EffectTableRow);
	void DeSpawnRangeEffect();
	

	void SpawnViewUI(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	FCircularActorPool<APawnRange> PawnRange;
};
