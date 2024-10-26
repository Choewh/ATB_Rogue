// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/SelectSubsystem.h"

void USelectSubsystem::AddPawn(ESpecies InSpecies)
{
	if (SelectPawns.Num() >= 5) { return; }
	SelectPawns.Add(InSpecies);
}

void USelectSubsystem::SetSelectablePawns(ESpecies InSelectable)
{
	SelectablePawns.Add(InSelectable);
}
