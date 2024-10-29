// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Env/SecondSkillableQuerier.h"
#include "Pawn/BasePawn.h"
#include "AI/EnemyAIController.h"
#include "AISystem.h"
#include "VisualLogger/VisualLogger.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/Env/BaseEnvQueryItemType_Actor.h"

void USecondSkillableQuerier::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	ABasePawn* QueryPawn = Cast<ABasePawn>(QueryOwner);
	if (QueryPawn == nullptr) { return; }
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(QueryPawn->GetController());
	UBaseEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyAIController->SecondSkillRangePawns);
}
