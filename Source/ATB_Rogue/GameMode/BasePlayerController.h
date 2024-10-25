// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Character/BaseCharacter.h"
#include "Camera/PawnViewCameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Enums/CameraViewMode.h"
#include "Enums/BattleState.h"
#include "Enums/ControllerInput.h"

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

	void SetupInputComponent();
	void OnLeftClick(const FInputActionValue& InputActionValue);
	void OnRightPress(const FInputActionValue& InputActionValue);
	void OnViewCameraMove(const FInputActionValue& InputActionValue);
	void OnViewAroundMove(const FInputActionValue& InputActionValue);

public:

	void CameraSet();

public:

	void Init(); // 관련함수 초기화

	bool PawnAroundView(ABasePawn* ViewEnemy);

	bool SetViewCameraMode(ECameraViewMode Cameramode);

	bool SetBattleState(EBattleState NewState);

public:
	UFUNCTION(BlueprintCallable, Category = "Move")
	void MoveCancle(); // 뒤로가기.

	FVector GetMovePoint() { return MovePoint; }

public:

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FShowWidget ShowWidget;

public:
	UPROPERTY()
	UInputMappingContext* IMC;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseCharacter> BasePlayer;

	UPROPERTY()
	class UBattleSubsystem* BattleSubsystem;

protected:
	UPROPERTY()
	FVector MovePoint = FVector::Zero();
	EControllerInput ControllerInput = EControllerInput::None;

	UPROPERTY(VisibleAnywhere)
	ECameraViewMode CameraViewMode = ECameraViewMode::DefaultView;

	UPROPERTY(VisibleAnywhere)
	EBattleState BattleState = EBattleState::Defalut;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DefaultCamera;

	UPROPERTY(VisibleAnywhere)
	UPawnViewCameraComponent* PawnViewCamera;



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
