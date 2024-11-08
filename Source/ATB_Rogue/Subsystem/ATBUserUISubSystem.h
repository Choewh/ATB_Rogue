// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ATBUserUISubSystem.generated.h"

class ABasePawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddPawnUI, ABasePawn*, InPawn);
/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UATBUserUISubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	
public :
	void BattleUIAddPawn(ABasePawn* InBasePawn);
	
public:
	UPROPERTY()
	FAddPawnUI AddPawnUI;
};
