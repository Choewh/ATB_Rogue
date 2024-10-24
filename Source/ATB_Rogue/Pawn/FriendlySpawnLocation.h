// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/SpawnTransform.h"
#include "FriendlySpawnLocation.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API AFriendlySpawnLocation : public ASpawnTransform
{
	GENERATED_BODY()
//protected:
	//virtual void BeginPlay() override;




protected:
	virtual void Destroyed() override;
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	TArray<ASpawnTransform*> PrevFriendlySpawnLocation;
#endif
public:

public:
	TArray<FTransform> GetSpawnTransform();
protected:
	ASpawnTransform* AddSpawnTransform(ASpawnTransform* InTemplate = nullptr);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnTransform")
	TArray<ASpawnTransform*> FriendlySpawnLocation;
};
