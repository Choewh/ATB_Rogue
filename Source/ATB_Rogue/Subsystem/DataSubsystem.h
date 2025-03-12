// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Misc/Datas.h"
#include "DataSubsystem.generated.h"

/**
 *
 */


UCLASS()
class ATB_ROGUE_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UDataSubsystem();

public:
	template <class T>
	T* GetDataTableRow(EDataTableType InData, ESpecies InSpecies);
	FEffectTableRow* GetEffect() { return EffectDataTable->FindRow<FEffectTableRow>("Default", "Not Found"); }
private:
	UDataTable* PawnDataTable;
	UDataTable* StatDataTable;
	UDataTable* SkillDataTable;
	UDataTable* EffectDataTable;
	UDataTable* AnimDataTable;
};

template <class T>
T* UDataSubsystem::GetDataTableRow(EDataTableType InData, ESpecies InSpecies)
{
    if (InSpecies == ESpecies::None) { return nullptr; }  // ✅ 한 번만 검사
    TArray<T*> Table_Array;
    UDataTable* TargetDataTable = nullptr;  // ✅ 공통 변수 사용
    // ✅ 선택한 데이터 테이블 가져오기
    switch (InData)
    {
    case EDataTableType::Pawn:      TargetDataTable = PawnDataTable; break;
    case EDataTableType::Status:    TargetDataTable = StatDataTable; break;
    case EDataTableType::Skill:     TargetDataTable = SkillDataTable; break;
    case EDataTableType::Effect:    TargetDataTable = EffectDataTable; break;
    case EDataTableType::Animation: TargetDataTable = AnimDataTable; break;
    default: return nullptr;
    }
    if (!TargetDataTable) { return nullptr; }  // ✅ Null 체크
    TargetDataTable->GetAllRows<T>(TEXT(""), Table_Array);
    // ✅ 데이터 찾기 (switch 문 밖으로 이동)
    for (auto& TableEntry : Table_Array)
    {
        if (TableEntry && TableEntry->Species == InSpecies)  // ✅ Null 체크 추가
        {
            return TableEntry;
        }
    }
    return nullptr;
}
