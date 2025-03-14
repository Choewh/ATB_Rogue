// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCameraManager/BasePlayerCameraManager.h"
#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/ATBUserUISubSystem.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "AI/EnemyAIController.h"
#include "Pawn/EnemyPawn.h"

//class AEnemyPawn;

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
		BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::StartBattle);
		BattleSubsystem->BattleStartTurn.AddDynamic(this, &ThisClass::StartTurn);
		BattleSubsystem->BattleFinishTurn.AddDynamic(this, &ThisClass::FinishTurn);
	}
	CameraSet();
	Init();
}

void ABasePlayerController::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (GetViewCameraMode() == ECameraViewMode::PawnView) { return; }

	if (ActionPawn)
	{
		ABaseAIController* ActionPawnController = Cast<ABaseAIController>(ActionPawn->GetController());
		float LerpSpeed = 1.0f;
		FVector NewLocation;
		FVector StartVec;
		FVector TargetVec;
		FVector MiddleVec;
		FRotator NewRotation;
		switch (ActionPawn->PawnGroup)
		{
		case EPawnGroup::Enemy:
			if (ActionPawnController->TargetPawn && GetViewCameraMode() == ECameraViewMode::Attack)
			{
				StartVec = ActionPawn->GetActorLocation();
				TargetVec = ActionPawnController->TargetPawn->GetActorLocation();
				MiddleVec = (StartVec + TargetVec) * 0.5f;

				NewLocation = FMath::VInterpTo(GetPawn()->GetActorLocation(), MiddleVec, DeltaTime, LerpSpeed);

				GetPawn()->SetActorLocation(NewLocation);
			}
			else
			{
				//카메라 위치와 회전 보간
				NewLocation = FMath::VInterpTo(GetPawn()->GetActorLocation(), ActionPawn->GetActorLocation(), DeltaTime, LerpSpeed);
				NewRotation = FMath::RInterpTo(GetPawn()->GetActorRotation(), ActionPawn->GetActorRotation(), DeltaTime, LerpSpeed);
				NewRotation.Roll = 0.f;
				GetPawn()->SetActorLocation(NewLocation);
				SetControlRotation(NewRotation);
				//GetPawn()->SetActorLocationAndRotation(ActionPawn->GetActorLocation(), ActionPawn->GetActorRotation());
			}
			break;
		case EPawnGroup::Friendly:
			if (ActionPawnController->TargetPawn && GetViewCameraMode() == ECameraViewMode::Attack)
			{
				StartVec = ActionPawn->GetActorLocation();
				TargetVec = ActionPawnController->TargetPawn->GetActorLocation();
				MiddleVec = (StartVec + TargetVec) * 0.5f;

				NewLocation = FMath::VInterpTo(GetPawn()->GetActorLocation(), MiddleVec, DeltaTime, LerpSpeed);

				GetPawn()->SetActorLocation(NewLocation);
			}
			else
			{
				//카메라 위치와 회전 보간
				NewLocation = FMath::VInterpTo(GetPawn()->GetActorLocation(), ActionPawn->GetActorLocation(), DeltaTime, LerpSpeed);
				NewRotation = FMath::RInterpTo(GetPawn()->GetActorRotation(), ActionPawn->GetActorRotation(), DeltaTime, LerpSpeed);
				NewRotation.Roll = 0.f;
				GetPawn()->SetActorLocation(NewLocation);
				AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(ActionPawnController);
				if (EnemyAIController)
				{
					SetControlRotation(NewRotation);
				}
			}
			break;
		default:
			break;
		}
	}
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
			DefaultCamera->SetFieldOfView(90.f);
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
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Menu")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ABasePlayerController::OnViewMenu);
	}
}


void ABasePlayerController::Init()
{
	DefaultCamera->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	CameraViewMode = ECameraViewMode::DefaultView;
	CameraViewUpdate();
	BattleState = EBattleState::Default;
	BattleStateUpdate();
	bMove = true;
}

void ABasePlayerController::CameraViewUpdate()
{
	switch (CameraViewMode)
	{
	case ECameraViewMode::DefaultView:
		DefaultCamera->SetActive(true);
		PawnViewCamera->SetView(false);
		PawnViewCamera->SetActive(false);
		break;

	case ECameraViewMode::PawnView:
		DefaultCamera->SetActive(false);
		PawnViewCamera->SetView(true);
		PawnViewCamera->SetActive(true);
		PawnViewCamera->OnPawnViewCamera(BattleSubsystem->GetActionPawn());
		break;

	case ECameraViewMode::Attack:
		DefaultCamera->SetActive(true);
		PawnViewCamera->SetView(false);
		PawnViewCamera->SetActive(false);
		break;

	case ECameraViewMode::Move:
		DefaultCamera->SetActive(true);
		PawnViewCamera->SetView(false);
		PawnViewCamera->SetActive(false);
		break;

	case ECameraViewMode::Follow:

		break;

	default:
		break;
	}
}

void ABasePlayerController::BattleStateUpdate()
{
	switch (BattleState)
	{
	case EBattleState::Default:
		break;
	case EBattleState::Move:
		break;
	case EBattleState::Attack:
		break;
	case EBattleState::Wait:
		break;
	case EBattleState::Finish:
		break;
	case EBattleState::Evolution:
		break;
	default:
		break;
	}
}

bool ABasePlayerController::CheckBattleState(EBattleState CheckBattleState)
{
	if (BattleState == CheckBattleState)
	{
		return true;
	}
	return false;
}

void ABasePlayerController::MoveCancle()
{
	ABasePawn* PlayeActionPawn = BattleSubsystem->GetActionPawn();
	if (PlayeActionPawn)
	{
		MovePoint = PlayeActionPawn->GetTargetLocation();
	}
}
void ABasePlayerController::StartBattle(uint8 Round)
{
	Init();
}

void ABasePlayerController::StartTurn()
{
	ABasePawn* InActionPawn = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn();
	if (InActionPawn)
	{
		ActionPawn = InActionPawn;
	}
}

void ABasePlayerController::FinishTurn()
{
	Init();
	if (ActionPawn)
	{
		ActionPawn = nullptr;
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
		GetWorld()->LineTraceSingleByProfile(HitResult, CameraLocation, EndPoint, TEXT("FloorTarget"), CollisionParams);
		//UKismetSystemLibrary::LineTraceSingleByProfile(CameraLocation, EndPoint )
		MovePoint = HitResult.ImpactPoint;
		GetWorld()->GetSubsystem<UActorpoolSubsystem>()->CursorEffectSpawn(HitResult.ImpactPoint);
		//로그
		{
			FString LogMessage = MovePoint.ToString();
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 1.f);
		}
	}
	else if (BattleState == EBattleState::Attack) // 폰 감지
	{
		FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		FHitResult CursorHitResult;
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, CursorHitResult);
		FVector CursorHitVector = CursorHitResult.ImpactPoint;
		TArray<FHitResult> HitResults;
		TArray<AActor*> IgnoreActors;
		bool bHit = UKismetSystemLibrary::SphereTraceMultiByProfile(this, CursorHitVector, CursorHitVector,
			50.f, TEXT("EnemyTarget"), false, IgnoreActors, EDrawDebugTrace::None,
			HitResults, true);
		//FCollisionQueryParams CollisionParams;
		//GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel5, CollisionParams);
		//UKismetSystemLibrary::LineTraceSingleByProfile(CameraLocation, EndPoint )
		if (bHit)
		{
			FHitResult ClosestHit;
			float ClosestDistance = FLT_MAX;
			AActor* ClosestActor = nullptr;

			for (const FHitResult& Hit : HitResults)
			{
				float Distance = FVector::Dist(CursorHitVector, Hit.ImpactPoint);

				ClosestActor = Hit.GetActor();
				AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(ClosestActor);

				if (!EnemyPawn) { continue; }

				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestHit = Hit;
				}
			}
			if (ClosestActor)
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *ClosestActor->GetName());
			}

			AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(ClosestActor);
			if (EnemyPawn)
			{
				BattleSubsystem->SelectTargetPawn(ClosestActor);
			}
		}
		// 배틀서브시스템의 Distance 체크 콜 셀렉한 스킬의 사거리 내에 있으면 사용할수 있다 하기 블랙보드 값 ESkill::~~
		//로그
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
	if ((BattleState == EBattleState::Attack || BattleState == EBattleState::Move) && ControllerInput == EControllerInput::MouseRight)
	{
		FRotator CurRotator = DefaultCamera->GetRelativeRotation();
		DefaultCamera->SetRelativeRotation(FRotator((CurRotator.Pitch - InputValue.Y), (CurRotator.Yaw - InputValue.X), 0));
	}
}

void ABasePlayerController::OnViewAroundMove(const FInputActionValue& InputActionValue)
{
	float InputValue = InputActionValue.Get<float>();

	if (BattleState == EBattleState::Move || BattleState == EBattleState::Attack)
	{
		AddYawInput(InputValue * 2.f);
	}
}

void ABasePlayerController::OnViewMenu(const FInputActionValue& InputActionValue)
{
	static UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
	check(ATBUserUISubSystem);
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			ATBUserUISubSystem->BattleUIMenu();
		});
	SetPause(true);
}


void ABasePlayerController::DrawRange(FVector CenterPoint, float Range, bool bPersistentLines)
{
	// 범위의 색상과 선 두께 설정
	FColor SphereColor = FColor::Red;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	//DrawDebugSphere(GetWorld(), CenterPoint, Range, 12, SphereColor, bPersistentLines, Duration);
}


