// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Pawn/BasePawn.h"
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
	UPROPERTY()
	TArray<ABasePawn*> PlayerPawns; //플레이어폰 자체만 담고있기 ㅇ 

public:
	UFUNCTION()
	TArray<ABasePawn*> GetPlayerPawn() { return PlayerPawns; } // 플레이어 폰 반환
	UFUNCTION()
	void SavePlayerPawns(TArray<ABasePawn*> InPlayerPawns) { PlayerPawns = InPlayerPawns; } // 플레이어 폰 받아 저장

public:
	//레벨 오픈 하면 플레이어 폰을 전달 | 델리게이트 ㄱ
	//다음 레벨 오픈전에 플레이어 폰을 받아서 PlayersPawns 에 저장 | 델리게이트 ㄱ
	//
	//UFUNCTOIN()
	//void PlayerSelectSpecies

};
