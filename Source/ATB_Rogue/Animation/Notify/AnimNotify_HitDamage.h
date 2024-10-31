// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_HitDamage.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAnimNotify_HitDamage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_HitDamage();

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
	
};
