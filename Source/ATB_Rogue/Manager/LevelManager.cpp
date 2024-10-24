// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/LevelManager.h"
#include "Misc/Utils.h"
#include "Pawn/EnemySpawnTransform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelManager::ALevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 여기서 허드 관리를 해줄지 고민
	//BattleSubsystem-
	//FEnemyPawns
}

void ALevelManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);
	Init();
}

void ALevelManager::Init()
{
	RoundsPawns.Empty();
	CurRound = 0;
	SetRoundPawns();
	SetRoundsTransform();
}

void ALevelManager::SetRoundPawns()
{
	for (uint8 i = 0; i < MaxRound; i++)
	{
		TArray<FBasePawnInfo> RoundPawns;
		if (i != BossRound)
		{
			RoundPawns = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateRoundSpecies(3, EPawnGroup::Enemy);
			RoundsPawns.Add(RoundPawns);
		}
		else
		{
			RoundPawns = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateRoundSpecies(3, EPawnGroup::Enemy, EBattleSpec::Boss);
			RoundsPawns.Add(RoundPawns);
		}
	}
}

void ALevelManager::SetRoundsTransform()
{
	TArray<AActor*> AllRoundTransforms;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AEnemySpawnTransform::StaticClass(), FName("RoundTransform"), AllRoundTransforms);
	for (uint8 i = 0; i < AllRoundTransforms.Num(); i++)
	{
		TArray<AActor*> RoundTransforms;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AEnemySpawnTransform::StaticClass(), FUtils::Round(i), RoundTransforms);
		//AEnemySpawnTransform* EnemySpawnTransform = Cast<AEnemySpawnTransform>(RoundTransforms[i]);
		//RoundsTransform.Add(EnemySpawnTransform->GetSpawnTransform());
		for (auto& Transforms : RoundTransforms)
		{
			AEnemySpawnTransform* EnemySpawnTransforms = Cast<AEnemySpawnTransform>(Transforms);
			RoundsTransform.Add(EnemySpawnTransforms->GetSpawnTransform());
		}
	}
}

// Called every frame

void ALevelManager::SpawnPawn()
{
	//EnemySpawn 액터를 찾아서 그 위치에 순서대로 배치 할지 고민

	for (uint8 i = 0; i < RoundsPawns[CurRound].Num(); i++)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ABasePawn* NewPawn = GetWorld()->SpawnActor<ABasePawn>(ABasePawn::StaticClass(), RoundsTransform[CurRound][i], ActorSpawnParameters);
		NewPawn->Species = RoundsPawns[CurRound][i].Species;
		NewPawn->PawnGroup = RoundsPawns[CurRound][i].PawnGroup;
		NewPawn->SetData();
		CurRoundPawns.Add(NewPawn);
	}
}

void ALevelManager::OnFirstSet(uint8 Round)
{
	SpawnPawn();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->SetEnemyPawns(CurRoundPawns);
}


