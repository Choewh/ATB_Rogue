// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/PawnViewCameraComponent.h"

#include "Misc/Utils.h"

#include "Pawn/FriendlySpawnLocation.h"

#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/EnemyCreateSubsystem.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());

	{
		UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);
		FTransform NewTransform = FTransform(FRotator(-10.f, 0.f, 0.f), FVector3d(-2000.f, 0.f, 1000.f)); // 음 맵? 
		Camera->SetRelativeTransform(NewTransform);
	}
	{
		UPawnViewCameraComponent* PawnViewCamera = CreateDefaultSubobject<UPawnViewCameraComponent>(TEXT("PawnViewCamera"));
		PawnViewCamera->SetupAttachment(RootComponent);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);
	Init();
}

void ABaseCharacter::Init()
{
	SetRoundsTransform();
}

void ABaseCharacter::SetRoundsTransform()
{
	TArray<AActor*> AllRoundTransforms;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AFriendlySpawnLocation::StaticClass(), FName("RoundTransform"), AllRoundTransforms);
	for (uint8 i = 0; i < AllRoundTransforms.Num(); i++)
	{
		TArray<AActor*> RoundTransforms;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AFriendlySpawnLocation::StaticClass(), FUtils::Round(i), RoundTransforms);
		//AEnemySpawnTransform* EnemySpawnTransform = Cast<AEnemySpawnTransform>(RoundTransforms[i]);
		//RoundsTransform.Add(EnemySpawnTransform->GetSpawnTransform());
		for (auto& Transforms : RoundTransforms)
		{
			AFriendlySpawnLocation* FriendlySpawnLocation = Cast<AFriendlySpawnLocation>(Transforms);
			RoundsTransform.Add(FriendlySpawnLocation->GetSpawnTransform());
		}
	}
}

void ABaseCharacter::SpawnPawn()
{
	for (uint8 i = 0; i < CurHavePawns.Num(); i++)
	{
		if (CurHavePawns.IsEmpty()) { break; } //비었으면 끝
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ABasePawn* NewPawn = GetWorld()->SpawnActor<ABasePawn>(ABasePawn::StaticClass(), RoundsTransform[(CurRound-1)%10][i], ActorSpawnParameters);
		NewPawn->Species = CurHavePawns[CurRound-1][i].Species;
		NewPawn->PawnGroup = CurHavePawns[CurRound-1][i].PawnGroup;
		NewPawn->SetData();
	}
}

void ABaseCharacter::OnFirstSet(uint8 Round)
{
}

///

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}