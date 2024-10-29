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

    EmptyCheck();
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
    uint8 RandomInt = FMath::RandRange(0, 2);

    
    switch (RandomInt)
    {
    case 0:
    {
        if (FirstEmpty) { PickRandomSkill(); break; }
        BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable1"), true);
        break;
    }
    case 1:
        if (SecondEmpty) { PickRandomSkill(); break; }
        BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable2"), true);
        break;
    case 2:
        if (ThirdEmpty) { PickRandomSkill(); break; }
        BlackboardComponent->SetValueAsBool(TEXT("bSkillAttackable3"), true);
        break;

    default:
        break;
    }
}
