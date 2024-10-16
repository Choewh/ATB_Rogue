// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Character/BaseCharacter.h"
#include "Pawn/BasePawn.h"
#include "Camera/CameraComponent.h"
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
	void MoveAccept(); // 서브시스템에 움직임 확정 / 좌표 전달 ->

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

	UCameraComponent* PawnViewCamera; 

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FShowWidget ShowWidget;

	bool bMove;
	bool isMove;

	bool bAttack;
	bool isAttack;

};
