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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBattleStartFirst, uint8 , First);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBattleStartSecond, uint8 , First);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleStartTurn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleFinishTurn);


UCLASS()
class ATB_ROGUE_API UBattleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadWrite)
	float FTest = 0.f;
	UBattleSubsystem();

	UFUNCTION(BlueprintCallable)
	void BattleStart(uint8 Round);

	UFUNCTION()
	void IsDieCheck();
	UFUNCTION()
	void SetEnemyPawns(TArray<ABasePawn*> InPawn) { EnemyPawns = InPawn; }
	UFUNCTION()
	void SetFriendlyPawns(TArray<ABasePawn*> InPawn) { FriendlyPawns = InPawn; }
	/*
	

	*/

public :
	//컨트롤러 에너미 추가
	UFUNCTION()
	void SetPlayerController(ABasePlayerController* Controller) { PlayerController = Controller; }
	//턴 시작
	UFUNCTION(BlueprintCallable)
	void EnterActiveTurn(ABasePawn* Enemy);
	//액션창
	UFUNCTION()
	void SelectActionView();

	UFUNCTION(BlueprintCallable)
	void SelectMoveAction();

	void ShowMoveRange();
	void HideMoveRange();
	UFUNCTION(BlueprintCallable)
	bool SelectMoveAccept();

	UFUNCTION(BlueprintCallable)
	void SelectMoveCancle();

	UFUNCTION(BlueprintCallable)
	void SelectAttackAction();

	UFUNCTION(BlueprintCallable)
	void SelectAbleFirstSkill();
	UFUNCTION(BlueprintCallable)
	void SelectAbleSecondSkill();
	UFUNCTION(BlueprintCallable)
	void SelectAbleThirdSkill();
	
	void SelectTargetPawn(AActor* TargetPawn);

	UFUNCTION(BlueprintCallable)
	void SelectAttackAccept();

	UFUNCTION(BlueprintCallable)
	void SelectAttackCancle();

	UFUNCTION(BlueprintCallable)
	void Evolution(); // Temp

	UFUNCTION()
	void MoveActionView();

	UFUNCTION()
	void AttackActionView();
	//턴종료
	UFUNCTION(BlueprintCallable)
	void FinishTurn();
	
private:
	void SetActionPawn(ABasePawn* NewPawn) { check(!ActionPawn); ActionPawn = NewPawn; }
public:
	UFUNCTION()
	void SetViewCameraMode(ECameraViewMode InViewMode);
	UFUNCTION()
	void SetBattleState(EBattleState InBattleState);


	ABasePawn* GetActionPawn() { return ActionPawn; }

	bool IsValidActionPawn() { return ActionPawn ? true : false; }
public:
	UPROPERTY(BlueprintAssignable)
	FBattleStartFirst BattleStartFirst;

	UPROPERTY(BlueprintAssignable)
	FBattleStartSecond BattleStartSecond;

	UPROPERTY(BlueprintAssignable)
	FBattleFinishTurn BattleFinishTurn;

	UPROPERTY(BlueprintAssignable)
	FBattleStartTurn BattleStartTurn;
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<ABasePawn*> EnemyPawns;
	UPROPERTY(BlueprintReadOnly)
	TArray<ABasePawn*> FriendlyPawns;

	UPROPERTY()
	ABasePawn* ActionPawn = nullptr;

	UPROPERTY()
	TObjectPtr<ABasePlayerController> PlayerController;

	//ABasePlayerController* PlayerController;
	/*
	Tarray<Player> ~
	Tarray<Enemy> ~ 
	*/
	
	
};
