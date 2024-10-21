// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "Pawn/BasePawn.h"
#include "ATBGameInstanceSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchSlider, ABasePawn*, MatchPawn);

UCLASS()
class ATB_ROGUE_API UATBGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UATBGameInstanceSubsystem();
	//Enemy 생성
	//랜덤으로 종 뽑아오는거 만들기
	UFUNCTION(BlueprintCallable, Category = "ATBGameInstanceSubsystem")
	void EntryEnemyPawn(ESpecies SpawnSpecies = ESpecies::None, EPawnGroup SpawnGroup = EPawnGroup::Defalut);//, FTransform SpawnTransform = FTransform::Identity); //
	
	TArray<TObjectPtr<ABasePawn>> GetPawns() const { return PawnsPool; }

	TArray<TObjectPtr<ABasePawn>> GetEnemyPawns();
	TArray<TObjectPtr<ABasePawn>> GetPlayerPawns();

	void ActivatePawn(ABasePawn* Pawn);
	void DeactivatePawn(ABasePawn* Pawn);

	TObjectPtr<ABasePawn> GetActorFromPool();

	TObjectPtr<ABasePawn> GetPoolingActor();
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ABasePawn>> PawnsPool; //둘다 담고있기 ㅇ 
private:
	//삭제하고 다음 라운드 폰 생성전에
	//void AddEnemy();
	//모두 PawnsPool로 반환한뒤 Enemy만 골라서 삭제
	//에너미폰만 지우는거 추가하기 EPawnGroup==Enemy로 체크 생각해보니 지울게 아님ㅁ 
	//void DeleteEnemy();
	void ReturnActorToPool(TObjectPtr<ABasePawn> Pawn);

	ESpecies GetRandomSpecies();//추후에는 레벨서브시스템에서 하는걸로

	TArray<TObjectPtr<ABasePawn>> ActivePawns; //플레이어폰 자체만 담고있기 ㅇ 
public:

	UPROPERTY(BlueprintAssignable)
	FMatchSlider MatchSlider;
};
