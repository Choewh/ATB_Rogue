// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/LevelManager.h"
#include "Misc/Utils.h"

#include "Pawn/EnemySpawnTransform.h"
#include "Subsystem/ATBUserUISubSystem.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelManager::ALevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 여기서 허드 관리를 해줄지 고민
	//BattleSubsystem-
	//레벨 매니저에 맵 매니저? 흠 서브시스템 ? 흠 다음레벨 관리 어떻게 할지 고민
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
	BattleSubsystem->BattleEndThird.AddDynamic(this, &ThisClass::NextLevel);
	BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);
	Init();
	//BattleSubsystem->BattleStart(CurRound);
}

void ALevelManager::Init()
{
	RoundsPawns.Empty();
	CurRound = 1;
	SetMaxRound();
	SetRoundsTransform();
	SetRoundPawns();
}

void ALevelManager::SetMaxRound()
{
	//라운드는 고정적으로 그냥 10씩 ㄱ
	MaxRound = 2; //TEMP 10 -> 2
	BossRound = MaxRound;
}

void ALevelManager::SetRoundPawns()
{
	//여기서 레벨 데이터와 종 배열 넘겨주기
	for (uint8 i = 1; i <= MaxRound; i++)
	{
		TArray<FBasePawnInfo> RoundPawns;
		if (i != BossRound)
		{																				//TEMP 1 해뒀는데 랜덤으로 나오게 ㄱ
			RoundPawns = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateRoundSpecies(1, EPawnGroup::Enemy, CurLevel);
			RoundsPawns.Add(RoundPawns);
		}
		else
		{
			RoundPawns = GetWorld()->GetSubsystem<UEnemyCreateSubsystem>()->CreateRoundSpecies(2, EPawnGroup::Enemy, CurLevel, EBattleSpec::Boss);
			RoundsPawns.Add(RoundPawns);
		}
	}
}

void ALevelManager::SetRoundsTransform()
{
	//디폴트 라운드 = RoundsTransform[0] , 보스 라운드 = RoundsTransform[1]
	//5개 다 추가해놓고 랜덤으로 2~5마리 생성하기? 
	TArray<AActor*> RoundTransforms;

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AEnemySpawnTransform::StaticClass(), FName("DefualtRound"), RoundTransforms);
	for (auto& Transforms : RoundTransforms)
	{
		AEnemySpawnTransform* EnemySpawnTransforms = Cast<AEnemySpawnTransform>(Transforms);
		RoundsTransform.Add(EnemySpawnTransforms->GetSpawnTransform());
	}

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AEnemySpawnTransform::StaticClass(), FName("BossRound"), RoundTransforms);
	for (auto& Transforms : RoundTransforms)
	{
		AEnemySpawnTransform* EnemySpawnTransforms = Cast<AEnemySpawnTransform>(Transforms);
		RoundsTransform.Add(EnemySpawnTransforms->GetSpawnTransform());
	}
}

// Called every frame

void ALevelManager::SpawnPawn()
{
	//EnemySpawn 액터를 찾아서 그 위치에 순서대로 배치 할지 고민
	uint8 Round = CurRound - 1;
	if (RoundsPawns[Round].IsEmpty()) { ensure(false); return; }
	for (uint8 i = RoundsPawns[Round].Num(); i > 0; i--)
	{
		if (RoundsPawns.IsEmpty()) { break; } //비었으면 끝
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		AEnemyPawn* NewPawn = nullptr;
		//보스 라운드 일반 라운드 따로하기 ㅇ
		if (CurRound == BossRound)
		{
			NewPawn = GetWorld()->SpawnActor<AEnemyPawn>(AEnemyPawn::StaticClass(), RoundsTransform[1][i - 1], ActorSpawnParameters);
			NewPawn->Species = RoundsPawns[Round][i - 1].Species;
			NewPawn->PawnGroup = RoundsPawns[Round][i - 1].PawnGroup;
			NewPawn->SetData();
			NewPawn->SetActorTransform(RoundsTransform[1][i - 1]);
		}
		else
		{
			NewPawn = GetWorld()->SpawnActor<AEnemyPawn>(AEnemyPawn::StaticClass(), RoundsTransform[0][i - 1], ActorSpawnParameters);
			NewPawn->Species = RoundsPawns[Round][i - 1].Species;
			NewPawn->PawnGroup = RoundsPawns[Round][i - 1].PawnGroup;
			NewPawn->SetData();
			NewPawn->SetActorTransform(RoundsTransform[0][i - 1]);
		}
		//
		UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
		check(ATBUserUISubSystem);
		ATBUserUISubSystem->BattleUIAddPawn(NewPawn);
		//TODO 생성하면서 구조체로 받은 SpeciesInfo 데이터를 추가해주기 라운드에 따른 레벨 ㅇ
		//TUniquePtr<FSpeciesInfo> SpeciesInfoPtr = MakeUnique<FSpeciesInfo>(RoundsPawns[Round][i - 1].SpeciesInfo);
		//NewPawn->StatusComponent->SetSpeciesInfo(SpeciesInfoPtr);                         

		NewPawn->OnSpawn();
		CurRoundPawns.Add(NewPawn);
		RoundsPawns[Round].RemoveAt(i - 1);
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
	CurRoundPawns.Empty();//전에 비우는건 공통이니까 ㄱ
	if (NextRound > MaxRound)
	{
		//다음 레벨로 넘어가기
		//지금은 그냥 레벨1로 넘어가기
		//넘어가기전에 플레이어 폰의 데이터 저장
		UGameplayStatics::OpenLevel(this, NextLevelName, true);
	}
	else
	{
		//다음라운드 시작하기
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->BattleStart(CurRound++);
	}
}


