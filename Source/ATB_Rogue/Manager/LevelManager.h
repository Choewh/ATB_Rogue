// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawn/EnemyPawn.h"
#include "Enums/Levels.h"
#include "Subsystem/BattleSubsystem.h"

#include "Subsystem/EnemyCreateSubsystem.h"

#include "LevelManager.generated.h"

//////////////////////////////



/// <summary>
/// 기본적으로 5라운드까지의 에너미의 정보 
/// </summary>
UCLASS()
class ATB_ROGUE_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Init();
	virtual void SetMaxRound();
	virtual void SetRoundPawns();
	virtual void SetRoundsTransform();
	virtual uint8 SetRandPawn();
public:
	UFUNCTION()
	virtual void SpawnPawn(); // 라운스 시작시 폰들 스폰 //배틀시스템->BattleStart 델리게이트 추가
	
	UFUNCTION(BlueprintCallable)
	void SetLevel(ELevels InLevel) { CurLevel = InLevel; }

	UFUNCTION()
	virtual void OnFirstSet(uint8 Round);

	UFUNCTION(BlueprintCallable)
	void NextLevel();
protected:
	//그냥 배열로 1234 ㄱ
	UPROPERTY(VisibleAnywhere)
	TArray<ABasePawn*> CurRoundPawns;
	TArray<TArray<FBasePawnInfo>> RoundsPawns; // 1~10 라운드까지 등장할 Pawns 배열
	TArray<TArray<FTransform>> RoundsTransform; //라운드별 소환 위치
private:
	UPROPERTY(EditAnywhere)
	FName NextLevelName;
	UPROPERTY(EditAnywhere)
	ELevels CurLevel;
	UPROPERTY(EditAnywhere)
	uint8 CurRound = 1;
	UPROPERTY(EditAnywhere)
	uint8 MaxRound = 10;
	UPROPERTY(EditAnywhere)
	uint8 BossRound = MaxRound;
};
