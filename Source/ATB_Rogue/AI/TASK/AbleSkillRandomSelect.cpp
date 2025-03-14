// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/AbleSkillRandomSelect.h"

UAbleSkillRandomSelect::UAbleSkillRandomSelect()
{
	NodeName = "AbleSkillRandomSelect";
}

EBTNodeResult::Type UAbleSkillRandomSelect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	SetOwner(BehaviorTreeComponent->GetOwner());
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	Init();
	EmptyCheck();
	if (FirstEmpty && SecondEmpty && ThirdEmpty) { return EBTNodeResult::Failed; }
	PickRandomSkill();


	return EBTNodeResult::Succeeded;
}

void UAbleSkillRandomSelect::EmptyCheck()
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(AIOwner);
	if (EnemyAIController->FirstSkillRangePawns.IsEmpty()) FirstEmpty = true;
	if (EnemyAIController->SecondSkillRangePawns.IsEmpty()) SecondEmpty = true;
	if (EnemyAIController->ThirdSkillRangePawns.IsEmpty()) ThirdEmpty = true;
}

void UAbleSkillRandomSelect::PickRandomSkill()
{
	ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
	uint8 RandomInt;

	if (Pawn->SkillComponent->SkillData->Skill_3)
	{
		RandomInt = FMath::RandRange(0, 2);
	}
	else
	{
		RandomInt = FMath::RandRange(0, 1);
	}


	switch (RandomInt)
	{
	case 0:
	{
		if (FirstEmpty) { PickRandomSkill(); break; }
		SelectAttackRandomPawn(ESkills::FirstSkill);
		UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////////FirstSkill")); //Temp
		break;
	}
	case 1:
		if (SecondEmpty) { PickRandomSkill(); break; }
		SelectAttackRandomPawn(ESkills::SecondSkill);
		UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////////SecondSkill")); //Temp
		break;
	case 2:
		if (ThirdEmpty) { PickRandomSkill(); break; }
		SelectAttackRandomPawn(ESkills::ThirdSkill);
		UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////////ThirdSkill")); //Temp
		break;

	default:
		break;
	}
}

void UAbleSkillRandomSelect::SelectAttackRandomPawn(ESkills Skill)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(AIOwner);
	uint8 RandomInt;
	BlackboardComponent->SetValueAsEnum(TEXT("Skill"), static_cast<uint8>(Skill));
	switch (Skill)
	{
	case ESkills::FirstSkill:
		RandomInt = FMath::RandRange(0, EnemyAIController->FirstSkillRangePawns.Num() - 1);
		EnemyAIController->TargetPawn = EnemyAIController->FirstSkillRangePawns[RandomInt];

		break;
	case ESkills::SecondSkill:
		RandomInt = FMath::RandRange(0, EnemyAIController->SecondSkillRangePawns.Num() - 1);
		EnemyAIController->TargetPawn = EnemyAIController->SecondSkillRangePawns[RandomInt];
		break;
	case ESkills::ThirdSkill:
		RandomInt = FMath::RandRange(0, EnemyAIController->ThirdSkillRangePawns.Num() - 1);
		EnemyAIController->TargetPawn = EnemyAIController->ThirdSkillRangePawns[RandomInt];
		break;
	default:
		break;
	}
	BlackboardComponent->SetValueAsObject(TEXT("TargetPawn"), EnemyAIController->TargetPawn);
	UE_LOG(LogTemp, Log, TEXT("Target Pawn : %s"),	*EnemyAIController->TargetPawn->GetName()); //Temp
}

void UAbleSkillRandomSelect::Init()
{
	FirstEmpty = false;
	SecondEmpty = false;
	ThirdEmpty = false;
}
