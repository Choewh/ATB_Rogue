// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ATBGameInstanceSubsystem.h"

UATBGameInstanceSubsystem::UATBGameInstanceSubsystem()
{
}
//
//TArray<ABasePawn*> Pawns; //둘다 담고있기 ㅇ 
//TArray<ABasePawn*> PlayerPawns; //플레이어폰 자체만 담고있기 ㅇ 
//TArray<ABasePawn*> EnemyPawns; //에너미폰 자체만 담고있기 ㅇ 
void UATBGameInstanceSubsystem::EntryEnemyPawn(ESpecies SpawnSpecies, EPawnGroup SpawnGroup)//, FTransform SpawnTransform)
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.ObjectFlags = RF_Transient; // 저장을 하지마라 라는 키워드
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABasePawn* NewPawn = GetWorld()->SpawnActor<ABasePawn>(ABasePawn::StaticClass(), ActorSpawnParameters);
	{
		if (SpawnSpecies == ESpecies::None)
		{
			SpawnSpecies = GetRandomSpecies();
		}
		//임시
		float RandomX = FMath::RandRange(-300, 300);
		float RandomY = FMath::RandRange(-300, 300);
		FVector Location(RandomX, RandomY, 0);

		NewPawn->PawnGroup = SpawnGroup;
		NewPawn->Species = SpawnSpecies;
		NewPawn->SetData();
		NewPawn->SetActorLocation(Location);
	}
	switch (SpawnGroup)
	{
	case EPawnGroup::Friendly:
		check(NewPawn);
		DeactivatePawn(NewPawn);
		PawnsPool.Add(NewPawn);
		break;
	case EPawnGroup::Enemy:
		check(NewPawn);
		DeactivatePawn(NewPawn);
		PawnsPool.Add(NewPawn);
		break;
	default:

		break;
	}
}

TObjectPtr<ABasePawn> UATBGameInstanceSubsystem::GetPoolingActor()
{
	{
		if (ActivePawns.IsEmpty())
		{
			return nullptr;
		}
		TObjectPtr<ABasePawn> Actor = ActivePawns.Top();
		return Actor;

	}
}

void UATBGameInstanceSubsystem::ReturnActorToPool(TObjectPtr<ABasePawn> Pawn)
{
	DeactivatePawn(Pawn);
	PawnsPool.Add(Pawn);
}

ESpecies UATBGameInstanceSubsystem::GetRandomSpecies()
{
	ESpecies Species = ESpecies::None;

	int32 Min = static_cast<int32>(ESpecies::Gigimon);
	int32 Max = static_cast<int32>(ESpecies::End);

	// 열거형의 범위 내에서 난수 생성
	int32 RandomIndex = FMath::RandRange(Min + 1, Max - 1);

	// 난수 값을 ESpecies로 변환하여 반환
	Species = static_cast<ESpecies>(RandomIndex);
	return Species;
}

TArray<TObjectPtr<ABasePawn>> UATBGameInstanceSubsystem::GetEnemyPawns()
{
	TArray<TObjectPtr<ABasePawn>> NewPawns;
	if (!PawnsPool.IsEmpty())
	{
		for (auto& Pawn : PawnsPool)
		{
			switch (Pawn->PawnGroup)
			{
			case EPawnGroup::Enemy:
				NewPawns.Add(Pawn);
				break;
			default:
				break;
			}
		}
	}
	return NewPawns;
}

TArray<TObjectPtr<ABasePawn>> UATBGameInstanceSubsystem::GetPlayerPawns()
{
	TArray<TObjectPtr<ABasePawn>> NewPawns;
	if (!PawnsPool.IsEmpty())
	{
		for (auto& Pawn : PawnsPool)
		{
			switch (Pawn->PawnGroup)
			{
			case EPawnGroup::Friendly:
				NewPawns.Add(Pawn);
				break;
			default:
				break;
			}
		}
	}
	return NewPawns;
}

void UATBGameInstanceSubsystem::ActivatePawn(ABasePawn* Actor)
{
	Actor->SetActorEnableCollision(true);
	Actor->SetActorHiddenInGame(false);
	Actor->SetActorTickEnabled(true);

	for (UActorComponent* Component : Actor->GetComponents())
	{
		Component->SetActive(true);
	}
}

void UATBGameInstanceSubsystem::DeactivatePawn(ABasePawn* Actor)
{
	Actor->SetActorEnableCollision(false);
	Actor->SetActorHiddenInGame(true);
	Actor->SetActorTickEnabled(false);

	for (UActorComponent* Component : Actor->GetComponents())
	{
		Component->SetActive(false);
	}
}

TObjectPtr<ABasePawn> UATBGameInstanceSubsystem::GetActorFromPool()
{
	if (PawnsPool.IsEmpty())
	{
		TObjectPtr<ABasePawn> ActiveActor = ActivePawns[0];
		ActivePawns.RemoveAt(0, EAllowShrinking::No);
		ReturnActorToPool(ActiveActor);
	}

	TObjectPtr<ABasePawn> Actor = PawnsPool.Pop(false);
	ActivePawns.Add(Actor);
	ActivatePawn(Actor);
	return Actor;
}

