// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAIController.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABasePawn* BasePawn = Cast<ABasePawn>(InPawn);
	if (!BasePawn) { return; }
	StatusComponentRef = BasePawn->GetComponentByClass<UStatusComponent>();
	SkillComponentRef = BasePawn->GetComponentByClass<USkillComponent>();
	// StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* OwningPawn = GetPawn();

	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();

	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), bMontagePlaying);

}

void ABaseAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}


void ABaseAIController::ResetValue()
{

}
