// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameMode/BasePlayerController.h"
#include "Pawn/BasePawn.h"
#include "BattleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UBattleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:
	UBattleSubsystem();
public :
	/*
	
	//Attack (타격자 , 피격자 , 스킬정보 데이터 테이블 , 스킬 이름 )?
	//EntryEnemy () // Tarray에 등록
	// ActiveTurn  ABT게이지 100시 호출 -> Tarray bActive False 로 변경 -> 턴 시작 (행동) / Todo -> 지금은 간단하게 마우스 좌표로 이동 -> 턴 종료 알림
	// 

	*/
	UFUNCTION()
	void SetPlayerController(ABasePlayerController* Controller) { PlayerController = Controller; }
	UFUNCTION(BlueprintCallable)
	void EntryEnemy(ABasePawn* EntryEnemy);

	UFUNCTION()
	void EnemyDeactive();
	UFUNCTION()
	void EnemyActive();

	UFUNCTION(BlueprintCallable)
	void ActiveTurn(ABasePawn* Enemy);
	
	UFUNCTION()
	void FinishTrun();
public:
	//공격 이동 대기
	//이동 확정시 호출 ㅇ
	UFUNCTION()
	void MoveTo(FVector TargetLocation);
	
private:
	void SetActionPawn(ABasePawn* NewPawn) { check(!ActionPawn); ActionPawn = NewPawn; }
public:
	ABasePawn* GetActionPawn() { return ActionPawn; }
public:
	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	TArray<ABasePawn*> GetPlayerblePawns() { return Playerble; }
	
	UFUNCTION(BlueprintPure, Category = "BattleSubsystem")
	bool IsBattle() { return OnBattle; }
private:
	UPROPERTY()
	TArray<ABasePawn*> Playerble;

	UPROPERTY()
	ABasePawn* ActionPawn;

	UPROPERTY()
	TObjectPtr<ABasePlayerController> PlayerController;

	//ABasePlayerController* PlayerController;
	/*
	Tarray<Player> ~
	Tarray<Enemy> ~ 
	*/
	UPROPERTY()
	bool OnBattle = false;
	
	
};
