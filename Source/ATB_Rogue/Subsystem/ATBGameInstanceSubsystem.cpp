// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBGameInstanceSubsystem.h"

//처음 플레이어 폰 생성시 호출
bool UATBGameInstanceSubsystem::InitSpawnPlayerPawnSpecies(TArray<ESpecies> InPlayerSpecies)
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
		FBasePawnInfo NewInfo = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateSpecies(EPawnGroup::Friendly, SelectPawnInfo, 5); //첫 생성시 레벨 5 
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

// BasePawn 을 받아서 스탯이랑 필요한 정보만 뽑아서 구조체로 저장하기
bool UATBGameInstanceSubsystem::SavePlayerPawnsInfo(TArray<ABasePawn*> InPlayerPawns)
{
	int InPawnsNum = InPlayerPawns.Num();
	if (InPawnsNum > 5) // 7개인적은 없었으니 대충 하나만 줄이기
	{
		InPlayerPawns.Pop();
		InPawnsNum = InPlayerPawns.Num();
	}
	
	//근데 레벨 넘어가면 사라져서 필요한가 싶네
	PlayerPawns = InPlayerPawns;

	//정보만 따로 빼서 구조체화 하기
	TArray<FBasePawnInfo> NewPlayerPawnsInfo;

	for (auto& Pawn : PlayerPawns) //TODO Destroy 하면 정보를 남기거나 여기서 그냥 null 이면 배열에서 빼기 
	{							//아니면 파괴된 폰은 따로 배열에 저장해놓고 생성시 추가해주기 ㄱ
		FBasePawnInfo NewBasePawnInfo;
		NewBasePawnInfo.SpeciesInfo = *Pawn->StatusComponent->GetSpeciesInfo();
		NewBasePawnInfo.Species = Pawn->Species;
		NewBasePawnInfo.PawnGroup = Pawn->PawnGroup;
		NewPlayerPawnsInfo.Add(NewBasePawnInfo);
	}
	
	PlayerPawnsInfo = NewPlayerPawnsInfo;

	if (InPawnsNum != PlayerPawns.Num())
	{
		return false;
	}
	return true;
}
