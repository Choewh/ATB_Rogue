// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Env/FirstSkillableQuerier.h"
#include "Pawn/BasePawn.h"
#include "AI/EnemyAIController.h"
#include "AISystem.h"
#include "VisualLogger/VisualLogger.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/Env/BaseEnvQueryItemType_Actor.h"

void UFirstSkillableQuerier::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	ABasePawn* QueryPawn = Cast<ABasePawn>(QueryOwner);
	if (QueryPawn == nullptr) { return; }
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(QueryPawn->GetController());
	//AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	//UE_CVLOG(GET_AI_CONFIG_VAR(bAllowControllersAsEQSQuerier) == false && Cast<AController>(QueryOwner) != nullptr, QueryOwner, LogEQS, Warning, TEXT("Using Controller as query's owner is dangerous since Controller's location is usually not what you expect it to be!"));
	UBaseEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyAIController->FirstSkillRangePawns);
}
