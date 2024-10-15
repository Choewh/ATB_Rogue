// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Pawn/BasePawn.h"

#include "BattleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBattleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public :
	/*
	
	//Attack (타격자 , 피격자 , 스킬정보 데이터 테이블 , 스킬 이름 )?
	//EntryEnemy () // Tarray에 등록
	// ActiveTurn  ABT게이지 100시 호출 -> Tarray bActive False 로 변경 -> 턴 시작 (행동) / Todo -> 지금은 간단하게 마우스 좌표로 이동 -> 턴 종료 알림
	// 

	*/
	UFUNCTION(BlueprintCallable)
	void EntryEnemy(ABasePawn* EntryEnemy);

	UFUNCTION()
	void EnemyDeactive();

	UFUNCTION(BlueprintCallable)
	void ActiveTurn(ABasePawn* Enemy);

public:
	//공격 이동 대기
	//이동 확정시 호출 ㅇ
	UFUNCTION()
	void MoveTo(ABasePawn* Enemy, FVector TargetLocation);

private:

private:
	UPROPERTY()
	TArray<ABasePawn*> Playerble;


	/*
	Tarray<Player> ~
	Tarray<Enemy> ~ 
	*/ 
	
	
};
