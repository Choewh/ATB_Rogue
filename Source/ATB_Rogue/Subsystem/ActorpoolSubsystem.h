// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
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
	void SpawnEnemy(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);
	void SpawnEffect(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);


	void SpawnRangeEffect(const FTransform SpawnTransform, UMaterial* DecalMaterial);

	void DeSpawnRangeEffect();
	void DeSpawnRangeEffect(APooledActor* DeSpawnActor);
	void SpawnViewUI(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	FCircularActorPool<APawnRange> PawnRange;
};
