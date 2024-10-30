// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "Enums/Species.h"
#include "AnimMontageTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FAnimMontageTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Species")
	ESpecies Species;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	UAnimMontage* FirstSkillReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	UAnimMontage* SecondReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	UAnimMontage* ThirdReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	UAnimMontage* HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	UAnimMontage* DieReactMontage;

};