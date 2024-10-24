// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Pawn/BasePawn.h"

#include "BaseCharacter.generated.h"

/// <summary>
/// 
/// 선택한 폰을 플레이어 폰풀에 추가
/// 
/// 레벨이 시작할때마다 플레이어폰을 받아옴
/// 레벨이 끝나면 플레이어폰의 필요정보를 저장
/// 
/// 
/// 그 외 레벨매니저와 동일
///
/// </summary>

UCLASS()
class ATB_ROGUE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;

	virtual void Init();
	virtual void SetRoundsTransform();



public:
	UFUNCTION()
	virtual void SpawnPawn(); // 라운스 시작시 폰들 스폰 //배틀시스템->BattleStart 델리게이트 추가

	UFUNCTION()
	virtual void OnFirstSet(uint8 Round); // 배틀 시작시 세팅해줘야할것들 ||배틀시스템 델리게이트ㄱ

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<ABasePawn*> CurHavePawns;
	TArray<TArray<FTransform>> RoundsTransform; //라운드별 소환 위치
private:
	//레벨별 라운드가 아닌 총 라운드
	UPROPERTY(EditAnywhere)
	uint8 CurRound = 1;
};
