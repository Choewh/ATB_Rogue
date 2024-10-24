// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Pawn/BasePawn.h"

#include "BaseCharacter.generated.h"

/// <summary>
/// 
/// ������ ���� �÷��̾� ��Ǯ�� �߰�
/// 
/// ������ �����Ҷ����� �÷��̾����� �޾ƿ�
/// ������ ������ �÷��̾����� �ʿ������� ����
/// 
/// 
/// �� �� �����Ŵ����� ����
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
	virtual void SpawnPawn(); // �� ���۽� ���� ���� //��Ʋ�ý���->BattleStart ��������Ʈ �߰�

	UFUNCTION()
	virtual void OnFirstSet(uint8 Round); // ��Ʋ ���۽� ����������Ұ͵� ||��Ʋ�ý��� ��������Ʈ��

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<ABasePawn*> CurHavePawns;
	TArray<TArray<FTransform>> RoundsTransform; //���庰 ��ȯ ��ġ
private:
	//������ ���尡 �ƴ� �� ����
	UPROPERTY(EditAnywhere)
	uint8 CurRound = 1;
};
