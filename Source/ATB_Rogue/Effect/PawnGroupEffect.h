// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pool/PooledActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Data/EffectTableRow.h"
#include "PawnGroupEffect.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API APawnGroupEffect : public APooledActor
{
	GENERATED_BODY()
	
public:
	APawnGroupEffect();

public:
	void SetData(FEffectTableRow& EffectData);
	void SetOwningPawn(AActor* InOwner);
	void HideEffect();
protected:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;

	//UFUNCTION()
	//virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot = nullptr;
	UPROPERTY(VisibleAnywhere)
	UDecalComponent* DecalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	AActor* OwningPawn;
	
	
};
