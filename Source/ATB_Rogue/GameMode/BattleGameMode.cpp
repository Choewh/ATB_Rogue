// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BattleGameMode.h"
#include "Subsystem/BattleSubSystem.h"
#include "GameMode/BasePlayerController.h"
#include "Character/BaseCharacter.h"
#include "GameMode/ATBHUD.h"
ABattleGameMode::ABattleGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	HUDClass = AATBHUD::StaticClass();
	DefaultPawnClass = ABaseCharacter::StaticClass();
}

void ABattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABattleGameMode::StartStage, 0.3f, false);
}

void ABattleGameMode::StartStage()
{
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	if (!ensure(BattleSubsystem)) // ensure�� ����Ͽ� ��Ÿ�ӿ����� ������ Ȯ��
	{
		UE_LOG(LogTemp, Error, TEXT("BattleSubsystem is nullptr in StartStage."));
		return;
	}
	BattleSubsystem->BattleStart(1);
}
