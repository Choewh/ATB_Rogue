// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/EnemyCreateSubsystem.h"



TArray<FBasePawnInfo> UEnemyCreateSubsystem::CreateRoundSpecies(uint8 MaxSpecies , EPawnGroup SpawnGroup , EBattleSpec BattleSpec)
{
	TArray<FBasePawnInfo> ReturnPawns;
	for (uint8 i = 0; i < MaxSpecies; i++)
	{
		if (BattleSpec == EBattleSpec::Boss)
		{
			//보스는 따로 생성
		}

		FBasePawnInfo NewSpecies = CreateSpecies(SpawnGroup);
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
	//임시 //만들어줄때 보스면 StatusComponent 불러서 보스 체크
	NewSpecies.PawnGroup = SpawnGroup;
	NewSpecies.Species = SpawnSpecies;
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
