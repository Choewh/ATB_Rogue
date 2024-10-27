// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Pawn/BasePawn.h"
#include "Enums/BattleSpec.h"
#include "EnemyCreateSubsystem.generated.h"

/**
 * 
 */
USTRUCT()
struct FBasePawnInfo
{
	GENERATED_BODY()
public:
	EPawnGroup PawnGroup;
	ESpecies Species;
};

UCLASS()
class ATB_ROGUE_API UEnemyCreateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	TArray<FBasePawnInfo> CreateRoundSpecies(uint8 MaxSpecies , EPawnGroup SpawnGroup, EBattleSpec BattleSpec = EBattleSpec::Defalut);//나중엔 레벨 종류도 받아서 맞는 폰 생성
	//폰 생성 정보 전달
	FBasePawnInfo CreateSpecies(EPawnGroup SpawnGroup,ESpecies SpawnSpecies = ESpecies::None);

	ESpecies GetRandomSpecies();//랜덤종
};
