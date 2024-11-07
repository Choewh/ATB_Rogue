// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBGameInstanceSubsystem.h"

bool UATBGameInstanceSubsystem::SavePlayerPawnsInfo(TArray<ESpecies> InPlayerSpecies)
{
	int InPawnsNum = InPlayerSpecies.Num();
	if (InPawnsNum > 5) // 7개인적은 없었으니 대충 하나만 줄이기
	{
		InPlayerSpecies.Pop();
		InPawnsNum = InPlayerSpecies.Num();
	}
	PlayerSpecies = InPlayerSpecies;
	
	for (auto& SelectPawnInfo : PlayerSpecies)
	{
		FBasePawnInfo NewInfo = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateSpecies(EPawnGroup::Friendly, SelectPawnInfo);
		PlayerPawnsInfo.Add(NewInfo);
	}

	if (InPawnsNum != PlayerPawnsInfo.Num())
	{
		return false;
	}
	return true;
}

//필요없는거같기도 라운드 -> 라운드 넘어갈땐 그냥 Location 만 수정해주기 체력과 스탯 그대로 
// 라운드 -> 레벨 
// Save Pawn Info 호출해서 스탯 구조체 , 종 // 추후 추가할거 있으면 적어두기
bool UATBGameInstanceSubsystem::SavePlayerPawns(TArray<ABasePawn*> InPlayerPawns)
{
	int InPawnsNum = InPlayerPawns.Num();
	if (InPawnsNum > 5) // 7개인적은 없었으니 대충 하나만 줄이기
	{
		InPlayerPawns.Pop();
		InPawnsNum = InPlayerPawns.Num();
	}

	PlayerPawns = InPlayerPawns;

	if (InPawnsNum != PlayerPawns.Num())
	{
		return false;
	}
	return true;
}
