// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Subsystem/BattleSubsystem.h"

ABasePlayerController::ABasePlayerController()
{
	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/IMC_Player.IMC_Player'") };
		check(Asset.Object);
		IMC = Asset.Object;
	}
	{

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
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ABasePlayerController::OnRightClick);
	}
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC, TEXT("IA_Mouse_Left")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Ongoing, this, &ABasePlayerController::OnLeftViewRotator);
	}

}


void ABasePlayerController::Init()
{
	//if(!PawnViewCamera && !DefaultCamera)
	//{
//	}

	bMove = true;
	isMove = false;

	bAttack = true;
	bAttack = false;

}

void ABasePlayerController::Cameraarrangement()
{
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	//카메라 이동 -> Show UI 그후는 알아서 ㅇ
	Init();
	ShowWidget.Broadcast();
	SetActionCamera();
	//SetActionCamera();
	//Pawn 이 스플라인이 있다면 PawnViewCamera 를 붙혀줌 BP_SplinCamera 참고
}


void ABasePlayerController::SetActionCamera()
{
	if (DefaultCamera->IsActive() && !isMove)
	{
		DefaultCamera->SetActive(false);
		PawnViewCamera->SetView(true);
		PawnViewCamera->SetActive(true);
		PawnViewCamera->OnPawnViewCamera();
	}
	else if (PawnViewCamera->IsActive() && isMove)
	{
		PawnViewCamera->SetView(false);
		PawnViewCamera->SetActive(false);
		DefaultCamera->SetActive(true);
	}
}

void ABasePlayerController::MoveEnter()
{
	if (!bMove) { return; }
	isMove = true;
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	FVector Center = ActionPawn->GetActorLocation();
	TargetLocation = Center;
	DrawRange(Center, 1000.f);
	{
		SetActionCamera();//
		//TargetLocation 좌표 찍기 편하게 전체가 보이게 카메라 위치 이동
	}
	//누를때마다 해당 좌표에 이펙트? 생성
}


void ABasePlayerController::MoveCancle()
{
	isMove = false;
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	if (ActionPawn)
	{
		TargetLocation = ActionPawn->GetTargetLocation();
		SetActionCamera();
	}
}

bool ABasePlayerController::MoveAccept()
{
	//배틀시스템에게 좌표 전달 후 이동 종료 bMove false?
	check(isMove);
	if (isMove)
	{
		if (MoveCheck())//지정된 범위내인지 확인하기
		{
			BattleSubsystem->MoveTo(TargetLocation);
			bMove = false; // bMove 를 배틀시스템에서 바꿔주는걸로 변경하기 
			SetActionCamera();
			isMove = false; 
			return true;
		}
		else //지정된 범위가 아니면 그냥 리턴
		{
			return false;
		}
	}
	return false;
}

bool ABasePlayerController::MoveCheck()
{
	ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
	FVector CenterPoint = ActionPawn->GetActorLocation();

	float Range = 1000.0f; // 설정한 범위 폰데이터를 받아와야함 배틀시스템에서 읽어오는걸 만들기?

	float Distance = FVector::Dist(CenterPoint, TargetLocation);

	if (Distance <= Range) {
		// 범위 내에 있는 경우
		UE_LOG(LogTemp, Warning, TEXT("Target is within range."));
		return true;
	}
	else {
		// 범위 밖인 경우
		UE_LOG(LogTemp, Warning, TEXT("Target is out of range."));
		return false;
	}
}

void ABasePlayerController::OnRightClick(const FInputActionValue& InputActionValue)
{
	if (isMove)
	{
		FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		FHitResult CursorHitResult;
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, CursorHitResult);
		FVector EndPoint = CursorHitResult.ImpactPoint;
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
		//UKismetSystemLibrary::LineTraceSingleByProfile(CameraLocation, EndPoint )
		TargetLocation = HitResult.ImpactPoint;
		//로그
		{
			FString LogMessage = TargetLocation.ToString();
			UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
			DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 1.f);
		}
	}
}

void ABasePlayerController::OnLeftViewRotator(const FInputActionValue& InputActionValue)
{
}


void ABasePlayerController::DrawRange(FVector CenterPoint, float Range, bool bPersistentLines)
{
	// 범위의 색상과 선 두께 설정
	FColor SphereColor = FColor::Red;
	float Duration = 5.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), CenterPoint, Range, 12, SphereColor, bPersistentLines, Duration);
}


