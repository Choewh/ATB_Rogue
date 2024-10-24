// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/SpawnTransform.h"
#include "EnemySpawnTransform.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AEnemySpawnTransform : public ASpawnTransform
{
	GENERATED_BODY()
//protected:
//	virtual void BeginPlay() override;

protected:
	virtual void Destroyed() override;

protected:
#if WITH_EDITOR && !UE_BUILD_SHIPPING

	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;


	TArray<ASpawnTransform*> PrevEnemySpawnTransform;
#endif
protected:
	UFUNCTION()
	ASpawnTransform* AddSpawnTransform(ASpawnTransform* InTemplate = nullptr);
public:
	UFUNCTION()
	TArray<FTransform> GetSpawnTransform();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnTransform")
	TArray<ASpawnTransform*> EnemySpawnTransform;
};
