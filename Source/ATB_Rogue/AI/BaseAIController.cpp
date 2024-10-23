// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Pawn/BasePawn.h"
#include "Kismet/KismetSystemLibrary.h"
void ABaseAIController::BeginPlay()
{
	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/BT_Pawn.BT_Pawn'"));
		check(BT);
		RunBehaviorTree(BT);
	}
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	if (!BasePawn) { return; }
	StatusComponentRef = BasePawn->GetComponentByClass<UStatusComponent>();
	BasePawn->OnMove.AddDynamic(this, &ThisClass::SetMovePoint);
	// StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* OwningPawn = GetPawn();
	ABasePawn* BasePawn = Cast<ABasePawn>(OwningPawn);
	float ABT = BasePawn->GetABT();
	bool check = IsFollowingAPath();

}

void ABaseAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}

//컨트롤러 -> 폰 -> 배틀
void ABaseAIController::SetMovePoint(FVector MovePoint)
{
	Blackboard->SetValueAsVector(TEXT("MovePoint"), MovePoint);
	Blackboard->SetValueAsBool(TEXT("bMove"), true);
	//EPathFollowingRequestResult::Type Result = MoveToLocation(MovePoint, 1000.f);
	UE_LOG(LogTemp, Log, TEXT("%s"), *MovePoint.ToString());
	//Blackboard->SetValueAsBool(TEXT("bMove"), false);
	//if(Result = EPathFollowingRequestResult::RequestSuccessful)
	
}

void ABaseAIController::ResetValue()
{

}
