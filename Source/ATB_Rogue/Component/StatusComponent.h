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
	//������ ���̺�
	UDataTable* StatDataTable;
	FStatTableRow* StatData;

public:
	//���Ȱ� �޾ƿ���
	EStage GetStage() { return Stage; }
	EAttribute GetAttribute() { return Attribute; }
	float GetStat(EStat StatName);
	float GetMoveRange() { return MoveRange; }

private:
	//��Ÿ ������
	UPROPERTY(VisibleAnywhere) EStage Stage;

	UPROPERTY(VisibleAnywhere) EAttribute Attribute;
	//���� �ʿ��� ���ȵ�
	UPROPERTY(VisibleAnywhere) float HP;       // ü��
	UPROPERTY(VisibleAnywhere) float ATK;      // ���ݷ�
	UPROPERTY(VisibleAnywhere) float DEF;      // ����
	UPROPERTY(VisibleAnywhere) float SPATK;    // Ư�� ����
	UPROPERTY(VisibleAnywhere) float SPDEF;    // Ư�� ���
	UPROPERTY(VisibleAnywhere) float SPD;      // ���ǵ�
	UPROPERTY(VisibleAnywhere) float ACC;      // ���߷�
	UPROPERTY(VisibleAnywhere) float EVA;      // ȸ����
	UPROPERTY(VisibleAnywhere) float MoveRange; // �̵� ���� �Ÿ�
};
