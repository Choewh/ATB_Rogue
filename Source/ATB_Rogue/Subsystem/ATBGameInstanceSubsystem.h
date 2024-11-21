	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystem/EnemyCreateSubsystem.h"
#include "ATBGameInstanceSubsystem.generated.h"

/**
 * 
 */


/// <summary>
/// 플레이어가 메뉴에서 선택한 폰 담아 저장
/// SelctPawn // 선택 -> 셀렉트폰 | 확인버튼 -> PlayerPawns에 추가 |
///									CreatePawn서브시스템에서 만들어 받기
/// </summary>
UCLASS()
class ATB_ROGUE_API UATBGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	TArray<FBasePawnInfo> GetPlayerPawnsInfo() { return PlayerPawnsInfo; } //플레이어폰 자체만 담고있기 ㅇ  
	UFUNCTION()
	uint16 GetFriendlyPawnsMinLevel();
	//스탯을 구조체로 폰마다 지니고있음 구조체가 Null 이면 기본 스탯입력.
	UFUNCTION()
	bool InitSpawnPlayerPawnSpecies(TArray<ESpecies> InPlayerSpeciesInfo);
	UFUNCTION()
	bool SavePlayerPawnsInfo(TArray<ABasePawn*> InPlayerPawns); // 플레이어 폰 받아 저장 ? 왜 필요없는거같은데 보고 지워주기 
															// 폰 레퍼런스 들고 있을 필요가 없는거같은디 라운드 - > 라운드 이동 라운드 -> 레벨 구조체로 저장 후 로드 
	UFUNCTION()
	void AddDiePawnInfo(ABasePawn* DiePawn);

	UFUNCTION()
	TArray<FBasePawnInfo> LoadPlayerPawnsInfo();

	UFUNCTION()
	TArray<ABasePawn*> GetPlayerPawn() { return PlayerPawns; } // 플레이어 폰 반환
	UFUNCTION()
	void NextRound() { Round++; }
public:
	UPROPERTY()
	TArray<FBasePawnInfo> PlayerPawnsInfo; //플레이어폰 자체만 담고있기 ㅇ 
	UPROPERTY()
	TArray<ABasePawn*> PlayerPawns; //플레이어폰 자체만 담고있기 ㅇ 
	UPROPERTY()
	TArray<FBasePawnInfo> PlayerAlivePawnsInfo;
	UPROPERTY()
	TArray<FBasePawnInfo> PlayerDiePawnsInfo;
	UPROPERTY()
	uint16 Round = 1;

public:
	//레벨 오픈 하면 플레이어 폰을 전달 | 델리게이트 ㄱ
	//다음 레벨 오픈전에 플레이어 폰을 받아서 PlayersPawns 에 저장 | 델리게이트 ㄱ
	//
	//UFUNCTOIN()
	//void PlayerSelectSpecies

};
