// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Pawn/BasePawn.h"
#include "Data/LevelTableRow.h"
#include "Enums/BattleSpec.h"
#include "Enums/Levels.h"
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
	TArray<FBasePawnInfo> CreateRoundSpecies(uint8 MaxSpecies , EPawnGroup SpawnGroup, ELevels Level = ELevels::None , EBattleSpec BattleSpec = EBattleSpec::Defalut);//나중엔 레벨 종류도 받아서 맞는 폰 생성
	//폰 생성 정보 전달
	FBasePawnInfo CreateSpecies(EPawnGroup SpawnGroup,ESpecies SpawnSpecies = ESpecies::None);
	FBasePawnInfo CreateSpeciesFromLevel(ELevels Level , EPawnGroup SpawnGroup = EPawnGroup::Enemy);


	ESpecies GetRandomSpecies();//랜덤종
	uint8 GetRandomSpecies(uint8 max);
public:
	// 서브시스템 초기화
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// 데이터 테이블 참조
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	UDataTable* LevelDataTable;
	FLevelTableRow* GetLevelDataById(ELevels Level) const;


private:
	// 데이터 테이블 경로로부터 데이터 테이블 로드
	void LoadDataTable();
};
