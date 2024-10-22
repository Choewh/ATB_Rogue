// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Subsystem/ATBGameInstanceSubsystem.h"
#include "GameMode/BasePlayerController.h"
#include "Engine/Texture2D.h"
#include "Pawn/BasePawn.h"
#include "BattleSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleStart);


UCLASS()
class ATB_ROGUE_API UBattleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:
	UBattleSubsystem();

	UFUNCTION(BlueprintCallable)
	void BattleStart();
	UFUNCTION(BlueprintCallable)
	void BattleEnd();
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
	void SetPortraits();
	//액션
	void PawnAction();
	//에너미 컨트롤 
	UFUNCTION()
	void PawnsDeactive();
	UFUNCTION()
	void PawnsActive();
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
	UPROPERTY(BlueprintAssignable)
	FBattleStart StartBattle;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ABasePawn>> Pawns;

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
