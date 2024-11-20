// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pool/PooledActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "CursorEffect.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API ACursorEffect : public APooledActor
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void PlayEffect();
public:
	ACursorEffect();

	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);

	UParticleSystemComponent* ParticleSystemComponent;
};
