// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/FriendlyPawn.h"
#include "Subsystem/ATBGameInstanceSubsystem.h"
#include "AI/FriendlyAIController.h"

AFriendlyPawn::AFriendlyPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AFriendlyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//죽으면 ATB시스템에 넘기기
	UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
	check(GameInstanceSubsystem);
	GameInstanceSubsystem->AddDiePawnInfo(this);

}


void AFriendlyPawn::BeginPlay()
{
	Super::BeginPlay();
	//SetActorRotation(FRotator(0.f, -90.f, 0.f));
}

void AFriendlyPawn::SetData()
{
	Super::SetData();

	AAIController* CurrentController = GetController<AAIController>();

	if (PawnData)
	{
		CollisionComponent->SetCollisionProfileName(TEXT("Friendly"));
	}
	// 현재 AI 컨트롤러 언포제스
	if (CurrentController)
	{
		CurrentController->UnPossess();

		// 기존 AI 컨트롤러 삭제 (선택 사항)
		CurrentController->Destroy();
	}
	if (bAuto) //컨트롤러를 만들어주는게 아니라 비헤이비어 트리 추가 or 변경 
	{
		AIControllerClass = PawnData->EnemyAIController;
	}
	else
	{
		AIControllerClass = PawnData->FriendlyAIController;
	}
	// 새로운 AI 컨트롤러 생성
	if (AIControllerClass)
	{
		// AI 컨트롤러를 월드에서 스폰
		AAIController* NewController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, GetActorLocation(), GetActorRotation());

		if (NewController)
		{
			// 새로운 컨트롤러가 Pawn을 소유하도록 설정
			NewController->Possess(this);
		}
	}
	// AIControllerClass = Cast<AFriendlyAIController>(PawnData->FriendlyAIController)->GetClass();
}
bool AFriendlyPawn::Movealbe(FVector NewDestination)
{
	//폰과 목표 사이거리 계산
	FVector CenterPoint = GetActorLocation();
	float Distance;
	Distance = FVector::Dist(CenterPoint, NewDestination);

	if (Distance <= 100.f) //이동거리가 너무 작으면 패스
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is too close."));
		return false;
	}
	else if (Distance <= StatusComponent->GetSpeciesInfo()->MoveRange)
	{
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

// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void AFriendlyPawn::MoveTo(FVector NewDestination)
{
	AFriendlyAIController* AIController = Cast<AFriendlyAIController>(GetController());
	//AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bMove"), true);
	AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("MovePoint"), NewDestination);
}

bool AFriendlyPawn::OnAutoPlay(bool Active)
{
	//FTransform OriginTransform = GetActorTransform();
	if (Active)
	{
		bAuto = true;
	}
	else
	{
		bAuto = false;
	}
	ABasePawn* NewTargetPawn;
	bool bAction;
	bool bMove;
	bool bAttack;

	AAIController* CurrentController = GetController<AAIController>();
	{
		ABaseAIController* BaseAIController = Cast<ABaseAIController>(CurrentController);
		NewTargetPawn = BaseAIController->TargetPawn;
		bAction = BaseAIController->GetBlackboardComponent()->GetValueAsBool(TEXT("bAction"));
		bMove = BaseAIController->GetBlackboardComponent()->GetValueAsBool(TEXT("bMove"));
		bAttack = BaseAIController->GetBlackboardComponent()->GetValueAsBool(TEXT("bAttack"));
	}
	if (PawnData)
	{
		CollisionComponent->SetCollisionProfileName(TEXT("Friendly"));
	}
	// 현재 AI 컨트롤러 언포제스
	if (CurrentController)
	{
		CurrentController->UnPossess();

		// 기존 AI 컨트롤러 삭제 (선택 사항)
		CurrentController->Destroy();
	}
	if (bAuto) //컨트롤러를 만들어주는게 아니라 비헤이비어 트리 추가 or 변경 
	{
		AIControllerClass = PawnData->EnemyAIController;
	}
	else
	{
		AIControllerClass = PawnData->FriendlyAIController;
	}
	// 새로운 AI 컨트롤러 생성
	if (AIControllerClass)
	{
		// AI 컨트롤러를 월드에서 스폰
		AAIController* NewController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, GetActorLocation(), GetActorRotation());

		if (NewController)
		{
			// 새로운 컨트롤러가 Pawn을 소유하도록 설정
			NewController->Possess(this);
			ABaseAIController* NewBaseAIController = Cast<ABaseAIController>(NewController);
			NewBaseAIController->TargetPawn = NewTargetPawn;
			NewBaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bAction"), bAction);
			NewBaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bMove"), bMove);
			NewBaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bAttack"), bAttack);
		}
	}

	//SetActorTransform(OriginTransform);
	return bAuto;
}
