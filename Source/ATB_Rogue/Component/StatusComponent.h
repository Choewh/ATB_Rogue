// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"
#include "Data/StatTableRow.h"

#include "Enums/Stat.h"
#include "Enums/Stage.h"
#include "Enums/Species.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATB_ROGUE_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void SetData(ESpecies InSpecies);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/// Script / Engine.DataTable'/Game/DataTable/StatTableRow.StatTableRow'

public:
	//데이터 테이블
	UDataTable* StatDataTable;
	FStatTableRow* StatData;

public:
	//스탯값 받아오기
	EStage GetStage() { return Stage; }
	EAttribute GetAttribute() { return Attribute; }
	float GetStat(EStat StatName);
	float GetMoveRange() { return MoveRange; }

private:
	//기타 데이터
	UPROPERTY(VisibleAnywhere) EStage Stage;

	UPROPERTY(VisibleAnywhere) EAttribute Attribute;
	//폰에 필요한 스탯들
	UPROPERTY(VisibleAnywhere) float HP;       // 체력
	UPROPERTY(VisibleAnywhere) float ATK;      // 공격력
	UPROPERTY(VisibleAnywhere) float DEF;      // 방어력
	UPROPERTY(VisibleAnywhere) float SPATK;    // 특수 공격
	UPROPERTY(VisibleAnywhere) float SPDEF;    // 특수 방어
	UPROPERTY(VisibleAnywhere) float SPD;      // 스피드
	UPROPERTY(VisibleAnywhere) float ACC;      // 명중률
	UPROPERTY(VisibleAnywhere) float EVA;      // 회피율
	UPROPERTY(VisibleAnywhere) float MoveRange; // 이동 가능 거리
};
