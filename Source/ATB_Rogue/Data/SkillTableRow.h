// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Species.h"
#include "Enums/SkillRange.h"
#include "Enums/HitDamageType.h"
#include "SkillTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FSkillTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Species")			ESpecies Species;
	
	UPROPERTY(EditAnywhere, Category = "Skill1") UTexture2D* Skill1_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill1") EHitDamageType Skill1_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill1") ESkillRange Skill1_Range;


	UPROPERTY(EditAnywhere, Category = "Skill2") UTexture2D* Skill2_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill2") EHitDamageType Skill2_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill2") ESkillRange Skill2_Range;
};