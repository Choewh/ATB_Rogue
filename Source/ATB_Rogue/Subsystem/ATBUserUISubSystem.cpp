// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBUserUISubSystem.h"
#include "Widget/ATBBattleUserWidget.h"
#include "ATBUserUISubSystem.h"

void UATBUserUISubSystem::UpdatePortrait(ABasePawn* UpdatePawn)
{
	UpdatePortraitUI.Broadcast(UpdatePawn);
}

void UATBUserUISubSystem::BattleUIAddPawn(ABasePawn* InBasePawn)
{
	AddPawnUI.Broadcast(InBasePawn);
}

void UATBUserUISubSystem::BattleUIRemovePawn(ABasePawn* InBasePawn)
{
	RemovePawnUI.Broadcast(InBasePawn);
}
