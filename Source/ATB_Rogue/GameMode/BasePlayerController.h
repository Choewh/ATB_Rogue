// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Character/BaseCharacter.h"
#include "Pawn/BasePawn.h"
#include "Camera/PawnViewCameraComponent.h"
#include "Camera/PlayerCameraManager.h"

#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowWidget);

/**
 *
 */
UCLASS()
class ATB_ROGUE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:



	ABasePlayerController();

	void BeginPlay();

public:


public:

	void OnRightClick(const FInputActionValue& InputActionValue);
	void OnLeftViewRotator(const FInputActionValue& InputActionValue);
	void SetupInputComponent();

public:

	void CameraSet();

public:

	void Init(); // 관련함수 초기화

	void Cameraarrangement();

public:
	//이동 공격 공통 카메라 위치로 이동
	void SetActionCamera();


	UFUNCTION(BlueprintCallable, Category = "Move")
	void MoveEnter(); // 우클릭시 받는 좌표를 목표 지점으로 삼아 좌표에 표식 찍어주기 / 

	UFUNCTION(BlueprintCallable, Category = "Move")
	void MoveCancle(); // 뒤로가기.
	UFUNCTION(BlueprintCallable, Category = "Move")
	bool MoveAccept(); // 서브시스템에 움직임 확정 / 좌표 전달 ->

	bool MoveCheck(); // TargetLocation이 이동가능한 범위내에 있는가 확인


public:

	UPROPERTY()
	UInputMappingContext* IMC;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	TObjectPtr<ABaseCharacter> BasePlayer;

	UPROPERTY()
	class UBattleSubsystem* BattleSubsystem;

	UCameraComponent* DefaultCamera;

	UPawnViewCameraComponent* PawnViewCamera;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FShowWidget ShowWidget;


	UPROPERTY(BlueprintReadOnly)
	bool bMove;
	UPROPERTY(BlueprintReadOnly)
	bool isMove;

	UPROPERTY(BlueprintReadOnly)
	bool bAttack;
	UPROPERTY(BlueprintReadOnly)
	bool isAttack;

private:
	void DrawRange(FVector CenterPoint, float Range, bool bPersistentLines = false);
};
