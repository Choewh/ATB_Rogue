// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/EnemyCreateSubsystem.h"


void UEnemyCreateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 데이터 테이블 로드
	LoadDataTable();
}

void UEnemyCreateSubsystem::LoadDataTable()
{
	LevelDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/LevelTableRow.LevelTableRow"));
	if (LevelDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Table 로드 성공"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Level Table 로드 실패"));
	}
}

FLevelTableRow* UEnemyCreateSubsystem::GetLevelDataById(ELevels Level) const
{
	if (LevelDataTable)
	{
		FString ContextString;
		FName RowName = *StaticEnum<ELevels>()->GetNameStringByValue(static_cast<int64>(Level));
		return LevelDataTable->FindRow<FLevelTableRow>(RowName, ContextString);
	}
	return nullptr;
}

//TArray<FBasePawnInfo> UEnemyCreateSubsystem::CreateRoundSpecies(uint8 MaxSpecies , EPawnGroup SpawnGroup , ELevels Level , EBattleSpec BattleSpec)
//{
//	TArray<FBasePawnInfo> ReturnPawns;
//	for (uint8 i = 0; i < MaxSpecies; i++)
//	{
//		if (BattleSpec == EBattleSpec::Boss)
//		{
//			보스는 따로 생성
//		}
//
//		FBasePawnInfo NewSpecies = CreateSpecies(SpawnGroup);
//		ReturnPawns.Add(NewSpecies);
//	}
//	return ReturnPawns;
//}

TArray<FBasePawnInfo> UEnemyCreateSubsystem::CreateRoundSpecies(uint8 MaxSpecies, EPawnGroup SpawnGroup, ELevels Level, EBattleSpec BattleSpec)
{
	TArray<FBasePawnInfo> ReturnPawns;
	for (uint8 i = 0; i < MaxSpecies; i++)
	{
		FBasePawnInfo NewSpecies;
		if (BattleSpec == EBattleSpec::Boss)
		{
			//보스는 따로 생성
			if (Level == ELevels::None) // 소환시 레벨환경제한이 없는 폰
			{
				NewSpecies = CreateSpecies(SpawnGroup);
			}
			else// 레벨이 있다는건 필요한 정보가 있다는거니까 ㅇ
			{

			}
		}
		
		if (Level == ELevels::None) // 소환시 레벨환경제한이 없는 폰
		{
			NewSpecies = CreateSpecies(SpawnGroup);
		}
		else// 레벨이 있다는건 필요한 정보가 있다는거니까 ㅇ
		{
			NewSpecies = CreateSpeciesFromLevel(Level, SpawnGroup);
		}
		//최종적으로 생성된 폰 소환
		ReturnPawns.Add(NewSpecies);
	}
	return ReturnPawns;
}


FBasePawnInfo UEnemyCreateSubsystem::CreateSpecies(EPawnGroup SpawnGroup, ESpecies SpawnSpecies)
{
	FBasePawnInfo NewSpecies;
	//랜덤
	if (SpawnSpecies == ESpecies::None)
	{
		SpawnSpecies = GetRandomSpecies();
	}
	//TEMP //만들어줄때 보스면 StatusComponent 불러서 보스 체크
	NewSpecies.PawnGroup = SpawnGroup;
	NewSpecies.Species = SpawnSpecies;
	return NewSpecies;
}

FBasePawnInfo UEnemyCreateSubsystem::CreateSpeciesFromLevel(ELevels Level, EPawnGroup SpawnGroup)
{
	FBasePawnInfo NewSpecies;
	NewSpecies.PawnGroup = SpawnGroup;
	//랜덤
	FLevelTableRow* LeveData = GetLevelDataById(Level);
	uint8 SpeciesIndex = GetRandomSpecies(LeveData->Species.Num()); //GetRandomSpecies안에서 -1 해주고있음
	NewSpecies.Species = LeveData->Species[SpeciesIndex];
	//TEMP //만들어줄때 보스면 StatusComponent 불러서 보스 체크

	return NewSpecies;
}

ESpecies UEnemyCreateSubsystem::GetRandomSpecies()
{
	ESpecies Species = ESpecies::None;

	int32 Min = static_cast<int32>(ESpecies::Gigimon);
	int32 Max = static_cast<int32>(ESpecies::End);

	// 열거형의 범위 내에서 난수 생성
	int32 RandomIndex = FMath::RandRange(Min + 1, Max - 1);

	// 난수 값을 ESpecies로 변환하여 반환
	Species = static_cast<ESpecies>(RandomIndex);
	return Species;
}

uint8 UEnemyCreateSubsystem::GetRandomSpecies(uint8 max)
{
	ESpecies Species = ESpecies::None;
	// 열거형의 범위 내에서 난수 생성
	uint8 RandomIndex = FMath::RandRange(0, max-1);

	// 난수 값을 ESpecies로 변환하여 반환
	return RandomIndex;
}

