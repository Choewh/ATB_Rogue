// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Enums/Species.h"
#include "SelectSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddSpecies, ESpecies, Species);

UCLASS()
class ATB_ROGUE_API USelectSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void AddPawn(ESpecies InSpecies);
	UFUNCTION(BlueprintCallable)
	void SetSelectablePawns(ESpecies InSelectable);
public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FAddSpecies AddSpecies;
	UPROPERTY(BlueprintReadWrite, Category = "SelectSubsystem")
	TArray<ESpecies> SelectablePawns;
	UPROPERTY(BlueprintReadOnly, Category = "SelectSubsystem")
	TArray<ESpecies> SelectPawns;
	
	
};
