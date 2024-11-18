// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectAbleSpecies.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum class ESelectAbleSpecies : uint8
{
	////유년기 2 부터 추가하기
	None = 0 UMETA(DisplayName = "None"),
	////BabyI
	//Jyarimon UMETA(DisplayName = "Jyarimon"),
	////BabyII
	//Gigimon UMETA(DisplayName = "Gigimon"),
	////Rookie
	Guilmon UMETA(DisplayName = "Guilmon"),
	Plotmon UMETA(DisplayName = "Plotmon"),
	 






	////Champion
	//Growmon UMETA(DisplayName = "Growmon"),
	////Ultimate
	//Megalogrowmon UMETA(DisplayName = "Megalogrowmon"),
	////Mege
	//Dukemon UMETA(DisplayName = "Dukemon"),
	End UMETA(DisplayName = "End")
};
