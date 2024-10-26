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

	UPROPERTY(EditAnywhere, Category = "Species")		ESpecies Species;

	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_1 = true;
	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_2 = true;
	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_3 = true;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "Skill1")		UTexture2D* Skill1_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill1|Damage")		EHitDamageType Skill1_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill1|Range")		ESkillRange Skill1_RangeType;
	UPROPERTY(EditAnywhere, Category = "Skill1|Range")		float Skill1_Range;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "Skill2")		UTexture2D* Skill2_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill2|Damage")		EHitDamageType Skill2_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill2|Range")		ESkillRange Skill2_RangeType;
	UPROPERTY(EditAnywhere, Category = "Skill2|Range")		float Skill2_Range;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "Skill3")		UTexture2D* Skill3_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill3|Damage")		EHitDamageType Skill3_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill3|Range")		ESkillRange Skill3_RangeType;
	UPROPERTY(EditAnywhere, Category = "Skill3|Range")		float Skill3_Range;
};