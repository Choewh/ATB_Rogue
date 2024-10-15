// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

ABasePlayerController::ABasePlayerController()
{
	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Player.IMC_Player'") };
		check(Asset.Object);
		IMC = Asset.Object;
	}
	bShowMouseCursor = true;

	//플레이어 카메라 추가
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC, 0);
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