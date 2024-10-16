// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/BattleSubsystem.h"

ABasePlayerController::ABasePlayerController()
{
	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Player.IMC_Player'") };
		check(Asset.Object);
		IMC = Asset.Object;
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
	CameraSet();
	//

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
	//카메라 껏다 켯다하는걸로 관리하기
	PawnViewCamera->SetActive(false);
}

void ABasePlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Right")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ABasePlayerController::OnRightClick);
	}

}


void ABasePlayerController::Init()
{
	bMove = true;
	isMove = false;

	bAttack = true;
	bAttack = false;
}

void ABasePlayerController::Cameraarrangement()
{
	Init();
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();

	//카메라 이동 -> Show UI 그후는 알아서 ㅇ
	ShowWidget.Broadcast();
	//Pawn 이 스플라인이 있다면 PawnViewCamera 를 붙혀줌 BP_SplinCamera 참고
}


void ABasePlayerController::SetActionCamera()
{

}

void ABasePlayerController::MoveEnter()
{
	isMove = true;
	//누를때마다 해당 좌표에 이펙트? 생성
}

void ABasePlayerController::MoveCancle()
{
	isMove = false;
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	if (ActionPawn)
	{
		TargetLocation = ActionPawn->GetTargetLocation();
	}
}

void ABasePlayerController::MoveAccept()
{
	//배틀시스템에게 좌표 전달 후 이동 종료 bMove false?
	check(isMove);
	if (isMove)
	{
		BattleSubsystem->MoveTo(TargetLocation);
	}
	bMove = false; // bMove 를 배틀시스템에서 바꿔주는걸로 변경하기 
}

void ABasePlayerController::OnRightClick(const FInputActionValue& InputActionValue)
{
	if (isMove)
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
			DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 1.f);
		}
	}
}

