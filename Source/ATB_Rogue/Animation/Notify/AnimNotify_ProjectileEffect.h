// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ProjectileEffect.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAnimNotify_ProjectileEffect : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_ProjectileEffect();

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere , Category ="SocketName")
	FName SocketName;
	UPROPERTY(EditAnywhere , Category = "Particle")
	UParticleSystem* ParticleSystem;
	UPROPERTY(EditAnywhere , Category = "Particle")
	UParticleSystem* HitParticleSystem;
};
