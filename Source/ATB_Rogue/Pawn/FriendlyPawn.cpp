// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/FriendlyPawn.h"
#include "AI/FriendlyAIController.h"

AFriendlyPawn::AFriendlyPawn(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

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

	if (Distance <= StatusComponent->GetSpeciesInfo()->MoveRange) {
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
	AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bMove"), true);
	AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("MovePoint"), NewDestination);
}