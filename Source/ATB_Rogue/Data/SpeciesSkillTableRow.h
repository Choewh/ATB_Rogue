// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Species.h"
#include "Enums/SkillRange.h"
#include "Enums/HitDamageType.h"
#include "Animation/AnimMontage.h"
#include "SpeciesSkillTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FSpeciesSkillTableRow : public FTableRowBase
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, Category = "Species")		ESpecies Species;

	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_1 = true;
	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_2 = true;
	UPROPERTY(EditAnywhere, Category = "SKills")		bool Skill_3 = true;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "FirstSkill", meta = (RowType = "/Script/KDT3D.WeaponTableRow"))
	FDataTableRowHandle FirstSkill;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "SecondSkill", meta = (RowType = "/Script/KDT3D.WeaponTableRow"))
	FDataTableRowHandle SecondSkill;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "ThirdSkill", meta = (RowType = "/Script/KDT3D.WeaponTableRow"))
	FDataTableRowHandle ThirdSkill;
};