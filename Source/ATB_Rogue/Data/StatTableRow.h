// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Attribute.h"
#include "Enums/Species.h"
#include "Enums/Stage.h"
#include "StatTableRow.generated.h"

USTRUCT()
struct ATB_ROGUE_API FStatTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FStatTableRow()
		: HP(100),
		ATK(10),
		DEF(10),
		SPATK(10),
		SPDEF(10),
		SPD(5),
		ACC(100),
		EVA(10),
		MoveRange(600.f)
	{
	}
public:
	UPROPERTY(EditAnywhere, Category = "Species")			ESpecies Species;
	UPROPERTY(EditAnywhere, Category = "Stage")				EStage Stage;
	UPROPERTY(EditAnywhere, Category = "Attribute")			EAttribute Attribute;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float HP = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float ATK = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float DEF = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float SPATK = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float SPDEF = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float SPD = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float ACC = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|Default")		float EVA = 0;
	UPROPERTY(EditAnywhere, Category = "Stat|MoveRange")	float MoveRange = 600.f;

};