// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BasePawn.h"
#include "Subsystem/BattleSubsystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	{
		//플레이어컨트롤 우클릭에 (타겟로케이션 업데이트) 함수 바인트해서 IsMoveAction 이면 업데이트
		//이동 확정 지으면 BattleSubsystem 호출 이동.

	}
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->EntryEnemy(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ABTFeeling();

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::ABTFeeling()
{
	if (!bActive)
	{
		return;
	}

	if (ABT_Cur >= ABT_MAX)
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->ActiveTurn(this);
	}
	else
	{
		ABT_Cur += ABT_Speed;
		//뷰포트 로그 float->string
		FString LogMessage = FString::Printf(TEXT("%f"), ABT_Cur);
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
	}
}

void ABasePawn::MoveTo()
{
	
}

