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
	CurRound = 1;
	SetMaxRound();
	SetRoundPawns();
	SetRoundsTransform();
}

void ALevelManager::SetMaxRound()
{
	TArray<AActor*> AllRoundTransforms;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AEnemySpawnTransform::StaticClass(), FName("RoundTransform"), AllRoundTransforms);
	MaxRound = AllRoundTransforms.Num();
	BossRound = MaxRound;
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
	if (RoundsPawns.IsEmpty()) { return; }
	uint8 Round = CurRound - 1;
	for (uint8 i = RoundsPawns[Round].Num(); i > 0 ; i--)
	{
		if (RoundsPawns.IsEmpty()) { break; } //비었으면 끝
		if (RoundsTransform[Round].IsEmpty()) { break; } //비었으면 끝
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ABasePawn* NewPawn = GetWorld()->SpawnActor<ABasePawn>(ABasePawn::StaticClass(), RoundsTransform[Round][i-1], ActorSpawnParameters);
		NewPawn->Species = RoundsPawns[Round][i-1].Species;
		NewPawn->PawnGroup = RoundsPawns[Round][i-1].PawnGroup;
		NewPawn->SetData();
		CurRoundPawns.Add(NewPawn);
		RoundsTransform[Round].RemoveAt(i-1);
		RoundsPawns[Round].RemoveAt(i-1);
	}
}

void ALevelManager::OnFirstSet(uint8 Round)
{
	SpawnPawn();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->SetEnemyPawns(CurRoundPawns);
}

void ALevelManager::NextLevel()
{
	uint8 NextRound = CurRound + 1;
	if (NextRound > MaxRound)
	{
		//다음 레벨로 넘어가기
	}
	else
	{
		CurRound++;
	}
}


