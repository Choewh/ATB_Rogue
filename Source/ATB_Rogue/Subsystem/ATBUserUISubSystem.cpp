// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBUserUISubSystem.h"
#include "Widget/ATBBattleUserWidget.h"
#include "ATBUserUISubSystem.h"

void UATBUserUISubSystem::BattleUIAddPawn(ABasePawn* InBasePawn)
{
	AddPawnUI.Broadcast(InBasePawn);
}
