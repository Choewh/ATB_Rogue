// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ATBUserUISubSystem.generated.h"

class ABasePawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddPawnUI, ABasePawn*, InPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemovePawnUI, ABasePawn*, DeadPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdatePawnUIUI, ABasePawn*, DeadPawn);
/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UATBUserUISubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	
public :
	UFUNCTION()
	void UpdatePawnUI(AActor* UpdatePawn);
	UFUNCTION()
	void BattleUIAddPawn(ABasePawn* InBasePawn);
	UFUNCTION()
	void BattleUIRemovePawn(ABasePawn* DeadPawn);
	
public:
	UPROPERTY()
	FAddPawnUI AddPawnUI;
	UPROPERTY()
	FRemovePawnUI RemovePawnUI;
	UPROPERTY()
	FUpdatePawnUIUI UpdatePawnUIUI;
};
