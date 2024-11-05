// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BattleGameMode.h"
#include "Subsystem/BattleSubSystem.h"
#include "GameMode/BasePlayerController.h"
#include "Character/BaseCharacter.h"
#include "GameMode/ABTHUD.h"
ABattleGameMode::ABattleGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	HUDClass = AABTHUD::StaticClass();
	DefaultPawnClass = ABaseCharacter::StaticClass();
}

void ABattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABattleGameMode::StartStage, 1.f, false);
}

void ABattleGameMode::StartStage()
{
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	if (!ensure(BattleSubsystem)) // ensure를 사용하여 런타임에서도 오류를 확인
	{
		UE_LOG(LogTemp, Error, TEXT("BattleSubsystem is nullptr in StartStage."));
		return;
	}
	BattleSubsystem->BattleStart(1);
}
