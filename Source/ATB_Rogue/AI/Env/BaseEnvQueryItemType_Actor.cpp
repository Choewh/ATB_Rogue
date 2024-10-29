// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Env/BaseEnvQueryItemType_Actor.h"
#include "UObject/WeakObjectPtr.h"
#include "GameFramework/Actor.h"
#include "AITypes.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

void UBaseEnvQueryItemType_Actor::SetContextHelper(FEnvQueryContextData& ContextData, const ABasePawn* SingleActor)
{
	ContextData.ValueType = UEnvQueryItemType_Actor::StaticClass();
	ContextData.NumValues = 1;
	ContextData.RawData.SetNumUninitialized(sizeof(FWeakObjectPtr));

	UEnvQueryItemType_Actor::SetValue(ContextData.RawData.GetData(), SingleActor);
}

void UBaseEnvQueryItemType_Actor::SetContextHelper(FEnvQueryContextData& ContextData, const TArray<ABasePawn*>& MultipleActors)
{
	ContextData.ValueType = UEnvQueryItemType_Actor::StaticClass();
	ContextData.NumValues = MultipleActors.Num();
	ContextData.RawData.SetNumUninitialized(sizeof(FWeakObjectPtr) * MultipleActors.Num());

	checkf(ContextData.RawData.Num() == sizeof(FWeakObjectPtr) * MultipleActors.Num(), TEXT("Failed to allocate the appropriate amount of memory"));

	uint8* RawData = (uint8*)ContextData.RawData.GetData();
	for (int32 ActorIndex = 0; ActorIndex < MultipleActors.Num(); ActorIndex++)
	{
		UEnvQueryItemType_Actor::SetValue(RawData, MultipleActors[ActorIndex]);
		RawData += sizeof(FWeakObjectPtr);
	}
}
