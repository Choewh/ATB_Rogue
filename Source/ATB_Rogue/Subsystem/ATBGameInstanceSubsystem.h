// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "Pawn/BasePawn.h"
#include "ATBGameInstanceSubsystem.generated.h"

/**
 * 
 */


UCLASS()
class ATB_ROGUE_API UATBGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	TArray<TObjectPtr<ABasePawn>> ActivePawns; //플레이어폰 자체만 담고있기 ㅇ 

};
