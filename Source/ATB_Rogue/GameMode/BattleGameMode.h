// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABattleGameMode();
protected:
	virtual void BeginPlay() override;

	void StartStage(); // 스테이지 시작 함수
	
};
