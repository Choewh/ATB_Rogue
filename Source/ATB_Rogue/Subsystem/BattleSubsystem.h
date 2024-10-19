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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetPortrait , UTexture* , NewPortrait );


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

	//컨트롤러 에너미 추가
	UFUNCTION()
	void SetPlayerController(ABasePlayerController* Controller) { PlayerController = Controller; }
	UFUNCTION(BlueprintCallable)
	void EntryEnemy(ABasePawn* EntryEnemy);
	//에너미 컨트롤 
	UFUNCTION()
	void EnemyDeactive();
	UFUNCTION()
	void EnemyActive();
	//턴시작
	UFUNCTION(BlueprintCallable)
	void EnterActiveTurn(ABasePawn* Enemy);
	//액션창
	UFUNCTION()
	void SelectActionView();

	UFUNCTION(BlueprintCallable)
	void SelectMoveAction();

	UFUNCTION(BlueprintCallable)
	bool SelectMoveAccept();

	UFUNCTION(BlueprintCallable)
	void SelectMoveCancle();

	UFUNCTION()
	void MoveActionView();

	UFUNCTION()
	void AttackActionView();
	//턴종료
	UFUNCTION()
	void FinishTrun();
	
private:
	void SetActionPawn(ABasePawn* NewPawn) { check(!ActionPawn); ActionPawn = NewPawn; }
public:
	ABasePawn* GetActionPawn() { return ActionPawn; }
	bool IsValidActionPawn() { return ActionPawn ? true : false; }
public:
	UFUNCTION(BlueprintCallable, Category = "BattleSubsystem")
	TArray<ABasePawn*> GetPlayerblePawns() { return Playerble; }

	UPROPERTY(BlueprintAssignable)
	FSetPortrait SetPortrait;

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
	
	
};
