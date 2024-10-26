// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBGameInstanceSubsystem.h"

bool UATBGameInstanceSubsystem::SavePlayerPawnsInfo(TArray<ESpecies> InPlayerSpecies)
{
	int InPawnsNum = InPlayerSpecies.Num();
	PlayerSpecies = InPlayerSpecies;
	
	for (auto& SelectPawnInfo : PlayerSpecies)
	{
		FBasePawnInfo NewInfo = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateSpecies(EPawnGroup::Friendly, SelectPawnInfo);
		PlayerPawnsInfo.Add(NewInfo);
	}

	if (InPawnsNum != PlayerSpecies.Num())
	{
		return false;
	}
	return true;
}

bool UATBGameInstanceSubsystem::SavePlayerPawns(TArray<ABasePawn*> InPlayerPawns)
{
	int InPawnsNum = InPlayerPawns.Num();
	PlayerPawns = InPlayerPawns;
	if (InPawnsNum != PlayerPawns.Num())
	{
		return false;
	}
	return true;
}
