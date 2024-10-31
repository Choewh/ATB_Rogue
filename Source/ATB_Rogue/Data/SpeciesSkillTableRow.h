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
	UPROPERTY(EditAnywhere , meta = (RowType = "/Script/ATB_Rogue.SkillTableRow"))
	FDataTableRowHandle FirstSkill;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ATB_Rogue.SkillTableRow"))
	FDataTableRowHandle SecondSkill;

	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ATB_Rogue.SkillTableRow"))
	FDataTableRowHandle ThirdSkill;
};