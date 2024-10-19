// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatTableRows.generated.h"

USTRUCT()
struct ATB_ROGUE_API FStatTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FStatTableRow()
		: HP(0),
		ATK(0),
		DEF(0),
		SPATK(0),
		SPDEF(0),
		SPD(0),
		ACC(0),
		EVA(0),
		MoveRange(1500.f)
	{
	}
public:

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float HP = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float ATK = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float DEF = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float SPATK = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float SPDEF = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float SPD = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float ACC = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|Default")
	float EVA = 0;

	UPROPERTY(EditAnywhere, Category = "Stat|MoveRange")
	float MoveRange = 1500.f;

};