// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCameraManager/BasePlayerCameraManager.h"
#include "Subsystem/BattleSubsystem.h"

ABasePlayerController::ABasePlayerController()
{
	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Player.IMC_Player'") };
		check(Asset.Object);
		IMC = Asset.Object;
	}
	{
		PlayerCameraManagerClass = ABasePlayerCameraManager::StaticClass();
		}
		bShowMouseCursor = true;

}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		Subsystem->AddMappingContext(IMC, 0);
	}
	{
		BasePlayer = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		check(BasePlayer);
	}
	{
		BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->SetPlayerController(this);
	}
	//

	//
	CameraSet();
	Init();
}

void ABasePlayerController::CameraSet()
{
	TArray<UCameraComponent*> Components;
	BasePlayer->GetComponents(UCameraComponent::StaticClass(), Components);
	for (auto& it : Components)
	{
		if (it->GetName() == TEXT("PawnViewCamera"))
		{
			PawnViewCamera = Cast<UPawnViewCameraComponent>(it);
			PawnViewCamera->SetActive(false);
		}
		else if (it->GetName() == TEXT("Camera"))
		{
			DefaultCamera = it;
		}
	}
	//카메라 껏다 켯다하는걸로 관리하기
}

void ABasePlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Right")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ABasePlayerController::OnRightPress);
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ABasePlayerController::OnRightPress);
	}
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Left")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ABasePlayerController::OnLeftClick);
	}
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Move")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnViewCameraMove);
	}
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Wheel")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ABasePlayerController::OnViewAroundMove);
	}

}


void ABasePlayerController::Init()
{
	DefaultCamera->SetRelativeRotation(FQuat::Identity);
	CameraViewMode = ECameraViewMode::DefaultView;
	BattleState = EBattleState::Defalut;
}

bool ABasePlayerController::PawnAroundView(ABasePawn* ViewEnemy)
{
	if (CameraViewMode != ECameraViewMode::PawnView)
	{
		SetViewCameraMode(ECameraViewMode::PawnView);
		PawnViewCamera->OnPawnViewCamera(ViewEnemy);
		return true;
	}
	else if(CameraViewMode == ECameraViewMode::PawnView)
	{
		PawnViewCamera->OnPawnViewCamera(ViewEnemy);
		return true;
	}
	return false;
}

bool ABasePlayerController::SetViewCameraMode(ECameraViewMode Cameramode)
{
	if (Cameramode == ECameraViewMode::DefaultView)
	{
		CameraViewMode = Cameramode;
		PawnViewCamera->SetView(false);
		PawnViewCamera->SetActive(false);
		DefaultCamera->SetActive(true);
		return true;
	}
	if (Cameramode == ECameraViewMode::PawnView)
	{
		CameraViewMode = Cameramode;
		DefaultCamera->SetActive(false);
		PawnViewCamera->SetView(true);
		PawnViewCamera->SetActive(true);
		return true;
	}
	return false;
}

bool ABasePlayerController::SetBattleState(EBattleState NewState)
{
	if (BattleState != NewState)
	{
		BattleState = NewState;
		return true;
	}
	return false;
}

void ABasePlayerController::MoveCancle()
{
	isMove = false;
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	if (ActionPawn)
	{
		MovePoint = ActionPawn->GetTargetLocation();
	}
}


void ABasePlayerController::OnLeftClick(const FInputActionValue& InputActionValue)
{
	if (BattleState == EBattleState::Move)
	{
		FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		FHitResult CursorHitResult;
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, CursorHitResult);
		FVector EndPoint = CursorHitResult.ImpactPoint;
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
		//UKismetSystemLibrary::LineTraceSingleByProfile(CameraLocation, EndPoint )
		MovePoint = HitResult.ImpactPoint;
		//로그
		{
			FString LogMessage = MovePoint.ToString();
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 1.f);
		}
	}
}

void ABasePlayerController::OnRightPress(const FInputActionValue& InputActionValue)
{
	switch (ControllerInput)
	{
	case EControllerInput::None:
		ControllerInput = EControllerInput::MouseRight;
		break;
	case EControllerInput::MouseRight:
		ControllerInput = EControllerInput::None;
		break;
	default:
		ControllerInput = EControllerInput::None;
		break;
	}
}

void ABasePlayerController::OnViewCameraMove(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	if (BattleState == EBattleState::Move && ControllerInput == EControllerInput::MouseRight)
	{
		FRotator CurRotator = DefaultCamera->GetRelativeRotation();
		DefaultCamera->SetRelativeRotation(FRotator((CurRotator.Pitch - InputValue.Y), (CurRotator.Yaw - InputValue.X), 0));
	}
}

void ABasePlayerController::OnViewAroundMove(const FInputActionValue& InputActionValue)
{
	float InputValue = InputActionValue.Get<float>();

	if (BattleState == EBattleState::Move)
	{
		AddYawInput(InputValue * 2.f);
			//float TargetYaw = BasePlayer->GetActorRotation().Yaw + (InputValue * 5.f);
			//float CurrentYaw = GetControlRotation().Yaw;
			//float SmoothYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, GetWorld()->GetDeltaSeconds(), 5.f);

			//// Yaw 값 업데이트
			//FRotator NewRotation = FRotator(0, SmoothYaw, 0);
			//BasePlayer->SetActorRotation(NewRotation);
	}
}


void ABasePlayerController::DrawRange(FVector CenterPoint, float Range, bool bPersistentLines)
{
	// 범위의 색상과 선 두께 설정
	FColor SphereColor = FColor::Red;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), CenterPoint, Range, 12, SphereColor, bPersistentLines, Duration);
}


