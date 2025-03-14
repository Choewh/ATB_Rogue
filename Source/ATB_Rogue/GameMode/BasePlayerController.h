// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Character/BaseCharacter.h"
#include "Camera/PawnViewCameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "AI/BaseAIController.h"
#include "Enums/CameraViewMode.h"
#include "Enums/BattleState.h"
#include "Enums/ControllerInput.h"

#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowTurnActionWidget);

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
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
public:


public:

	void SetupInputComponent();
	void OnLeftClick(const FInputActionValue& InputActionValue);
	void OnRightPress(const FInputActionValue& InputActionValue);
	void OnViewCameraMove(const FInputActionValue& InputActionValue);
	void OnViewAroundMove(const FInputActionValue& InputActionValue);
	void OnViewMenu(const FInputActionValue& InputActionValue);
public:

	void CameraSet();

public:
	UFUNCTION()
	void Init(); // 관련함수 초기화

	void CameraViewUpdate();

	void SetViewCameraMode(ECameraViewMode Cameramode) { CameraViewMode = Cameramode; }

	ECameraViewMode GetViewCameraMode() { return CameraViewMode; }

	void BattleStateUpdate();

	void SetBattleState(EBattleState NewState) { BattleState = NewState; }

	UFUNCTION(BlueprintCallable)
	bool CheckBattleState(EBattleState CheckBattleState);

public:
	UFUNCTION(BlueprintCallable, Category = "Move")
	void MoveCancle(); // 뒤로가기.


	UFUNCTION(BlueprintCallable, Category = "Move")
	bool IsMove() { return bMove; }

	void SetMoveActive(bool Active) { bMove = Active; }

	FVector GetMovePoint() { return MovePoint; }

public:

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FShowTurnActionWidget ShowTurnActionWidget;

	UFUNCTION()
	void StartBattle(uint8 Round);
	UFUNCTION()
	void StartTurn();
	UFUNCTION()
	void FinishTurn();
public:
	UPROPERTY()
	UInputMappingContext* IMC;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseCharacter> BasePlayer;

	UPROPERTY()
	class UBattleSubsystem* BattleSubsystem;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DefaultCamera;

	UPROPERTY(VisibleAnywhere)
	UPawnViewCameraComponent* PawnViewCamera;

protected:
	UPROPERTY()
	FVector MovePoint = FVector::Zero();
	EControllerInput ControllerInput = EControllerInput::None;

	UPROPERTY(VisibleAnywhere)
	ECameraViewMode CameraViewMode = ECameraViewMode::DefaultView;

	UPROPERTY(VisibleAnywhere)
	EBattleState BattleState = EBattleState::Default;

	UPROPERTY(VisibleAnywhere)
	ABasePawn* ActionPawn;

	UPROPERTY(BlueprintReadOnly)
	bool bMove;
	UPROPERTY(BlueprintReadOnly)
	bool bAttack;

	//오토 설정 여기서 할지 생각해보기
private:
	void DrawRange(FVector CenterPoint, float Range, bool bPersistentLines = false);
};
