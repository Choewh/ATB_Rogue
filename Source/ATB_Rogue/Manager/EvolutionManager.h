// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enums/Species.h"
#include "Engine/DataTable.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Data/PawnTableRow.h"
#include "Data/AnimMontageTableRow.h"
#include "Components/TimelineComponent.h"
#include "EvolutionManager.generated.h"

UCLASS()
class ATB_ROGUE_API AEvolutionManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEvolutionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

public:

	//애니메이션 시작
	UFUNCTION()
	void PlayEvolutionSequence(ESpecies InSpecies);
	void SetData(ESpecies InSpecies); // 메쉬와 애니메이션 설정

	UFUNCTION(BlueprintCallable)
	void EvolutionAnimation();
	UFUNCTION(BlueprintCallable)
	void UpdateEvolutionPawnMesh();

	UFUNCTION()
	void StartEvolution();
	UFUNCTION()
	void OnDestroyEffect(float InDissolve);
	UFUNCTION()
	void OnDestroyEffectEnd();
	UFUNCTION()
	void OnSpawn();
	UFUNCTION()
	void OnSpawnEffect(float InDissolve);
	UFUNCTION()
	void OnSpawnEffectEnd();
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void MaterialInit();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Evolution")
	UAnimMontage* EvoReactMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Evolution")
	USkeletalMesh* EvolutionSkeletalMesh;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DestroyEffectTimelineComponent;
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* SpawnEffectTimelineComponent;
	TArray<UMaterialInstanceDynamic*> MaterialInstanceDynamics;
private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UDataTable* PawnDataTable;
	UDataTable* AnimDataTable;
	FPawnTableRow* PawnData;
	FAnimMontageTableRow* AnimData;
	UPROPERTY(VisibleAnywhere)
	ULevelSequence* LevelSequence;

	UPROPERTY(VisibleAnywhere)
	ALevelSequenceActor* LevelSequenceActor;

	UPROPERTY(VisibleAnywhere)
	ULevelSequencePlayer* LevelSequencePlayer;

	bool bEvolution = false;
};
