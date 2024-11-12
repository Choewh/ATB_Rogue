// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBUserUISubSystem.h"
#include "Widget/ATBBattleUserWidget.h"
#include "ATBUserUISubSystem.h"

void UATBUserUISubSystem::UpdatePawnUI(AActor* UpdatePawn)
{
	ABasePawn* UpdateBasePawn = Cast<ABasePawn>(UpdatePawn);
	if (!UpdateBasePawn) { return; }
	UpdatePawnUIUI.Broadcast(UpdateBasePawn);
}

void UATBUserUISubSystem::BattleUIAddPawn(ABasePawn* InBasePawn)
{
	AddPawnUI.Broadcast(InBasePawn);
}

void UATBUserUISubSystem::BattleUIRemovePawn(ABasePawn* InBasePawn)
{
	RemovePawnUI.Broadcast(InBasePawn);
}
