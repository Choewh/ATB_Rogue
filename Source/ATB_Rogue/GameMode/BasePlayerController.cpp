// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController()
{
	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Player.IMC_Player'") };
		check(Asset.Object);
		IMC = Asset.Object;
	}
	bShowMouseCursor = true;

	//플레이어 카메라 추가;
	//SetViewTarget(DefaultCamera);
	//PawnViewCamera 는 액터의 자식으로 넣어줌
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC, 0);
	BasePlayer = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	check(BasePlayer);
	CameraSet();
}

void ABasePlayerController::CameraSet()
{
	TArray<UCameraComponent*> Components;
	BasePlayer->GetComponents(UCameraComponent::StaticClass(), Components);
	for (auto& it : Components)
	{
		if (it->GetName() == TEXT("PawnViewCamera"))
		{
			PawnViewCamera = it;
		}
		else if (it->GetName() == TEXT("Camera"))
		{
			DefaultCamera = it;
		}
	}
	//카메라 전환 함수. 처음에는 디폴트 카메라로 설정
	//{
	//	FViewTargetTransitionParams TransitionParams;
	//	TransitionParams.BlendTime = 1.0f; // 전환 시간 (초)
	//	TransitionParams.BlendFunction = EViewTargetBlendFunction::VTBlend_Cubic; // 블렌딩 함수
	//	SetViewTarget(DefaultCamera->GetOwner(), TransitionParams);
	//}
	PawnViewCamera->SetActive(false);
	//DefaultCamera->SetActive(false);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	//if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_CameraMove")))
	//{
	//	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	//}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Right")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnRightClick);
	}
}


void ABasePlayerController::Cameraarrangement(APawn* InPawn)
{
	//Pawn 이 스플라인이 있다면 PawnViewCamera 를 붙혀줌 BP_SplinCamera 참고
}

FVector ABasePlayerController::NewDestination()
{
	//HUD 에서 이동 확정을 누르면 호출 하는걸로 변경
	return FVector::One();
}

//
//void ABasePlayerController::OnMove(const FInputActionValue& InputActionValue)
//{
//	FVector2D ActionInput = InputActionValue.Get<FVector2D>();
//
//	AddYawInput(ActionInput.X);
//	AddPitchInput(ActionInput.Y);
//}

void ABasePlayerController::OnRightClick(const FInputActionValue& InputActionValue)
{
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation(); //Start
	FHitResult CursorHitResult; 
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, CursorHitResult);
	FVector EndPoint = CursorHitResult.ImpactPoint;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
	//UKismetSystemLibrary::LineTraceSingleByProfile(CameraLocation, EndPoint, )
	TargetLocation = HitResult.ImpactPoint;
	//로그
	{
		FString LogMessage = TargetLocation.ToString();
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
		DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
	}
}