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
	TSharedPtr<FSpeciesInfo> SpeciesInfo; //일단 생각해보기 
	FBasePawnInfo()
		:
		PawnGroup(EPawnGroup::Default),
		Species(ESpecies::None),
		SpeciesInfo(MakeShared<FSpeciesInfo>())
	{}

	FBasePawnInfo(const FBasePawnInfo& Other)
		:
		PawnGroup(Other.PawnGroup),
		Species(Other.Species),
		SpeciesInfo(Other.SpeciesInfo)
	{}

	FBasePawnInfo& operator=(const FBasePawnInfo& Other) {
		if (this != &Other) {
			this->PawnGroup = Other.PawnGroup;
			this->Species = Other.Species;
			this->SpeciesInfo = Other.SpeciesInfo;
		}
		return *this;
	}
};

UCLASS()
class ATB_ROGUE_API UEnemyCreateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	//에너미 생성시 레벨 정보 설정 어디서 할지 고민 TODO
	TArray<FBasePawnInfo> CreateRoundSpecies(uint8 MaxSpecies , EPawnGroup SpawnGroup, ELevels Level = ELevels::None , EBattleSpec BattleSpec = EBattleSpec::Default);//나중엔 레벨 종류도 받아서 맞는 폰 생성
	//폰 생성 정보 전달 스탯 구조체 있는지 확인
	FBasePawnInfo CreateSpecies(EPawnGroup SpawnGroup, EBattleSpec BattleSpec, uint8 Level = 1, ESpecies SpawnSpecies = ESpecies::None);
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
