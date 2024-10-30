// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Species.h"
#include "Enums/SkillRange.h"
#include "Enums/HitDamageType.h"
#include "Enums/HitTargetType.h"
#include "SkillTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FSkillTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Skill|Icon")			UTexture2D* Skill_Icon;
	UPROPERTY(EditAnywhere, Category = "Skill|Name")			FName Skill_Name;
	UPROPERTY(EditAnywhere, Category = "Skill|DamageType ")		EHitDamageType Skill_DamageType;
	UPROPERTY(EditAnywhere, Category = "Skill|RangeType")		ESkillRange Skill_RangeType;
	UPROPERTY(EditAnywhere, Category = "Skill|TargetType ")		EHitTargetType Skill_TargetType;
	UPROPERTY(EditAnywhere, Category = "Skill|Range")			float Skill_Range;
	UPROPERTY(EditAnywhere, Category = "Skill|Animation")		UAnimMontage* SkillReactMontage;

};