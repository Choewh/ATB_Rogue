// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"


#include "Misc/Utils.h"

#include "Subsystem/BattleSubsystem.h"
#include "Pawn/FriendlySpawnLocation.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

class ABasePlayerController;

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PawnViewCameraComponent = CreateDefaultSubobject<UPawnViewCameraComponent>(TEXT("PawnViewCamera"));
	{
		SpringArmComponent->SetupAttachment(GetMesh());
		SpringArmComponent->TargetArmLength = 1500.f;
		SpringArmComponent->ProbeSize = 5.0;
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bEnableCameraRotationLag = true;
		SpringArmComponent->CameraRotationLagSpeed = 1.f;
		SpringArmComponent->SetUsingAbsoluteRotation(false);
	}
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
		FTransform NewTransform = FTransform(FRotator(-30.f, 0.f, 0.f), FVector3d(0.f, 0.f, 800.f)); // 음 맵? 
		CameraComponent->SetRelativeTransform(NewTransform);
	}
	{
		PawnViewCameraComponent->SetupAttachment(RootComponent);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABasePawn* ActionPawn = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn();
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController());
	if (ActionPawn)
	{
		float LerpSpeed = 5.0f;
		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ActionPawn->GetActorLocation(), DeltaTime, LerpSpeed);
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), ActionPawn->GetActorRotation(), DeltaTime, LerpSpeed);


		FVector StartVec = CameraComponent->GetComponentLocation();
		FVector TargetVec = ActionPawn->GetActorLocation();

		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);
		SpringArmComponent->SetWorldRotation(LookAtRotator);
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//레벨 시작시 Instance 에서 폰정보를 받아옴
	{
		UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
		PlayerPawnsInfo = GameInstanceSubsystem->GetPlayerPawnsInfo();
	}
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);
	}
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
	for (uint8 i = 0; i < PlayerPawnsInfo.Num(); i++)
	{
		if (PlayerPawnsInfo.IsEmpty()) { break; } //비었으면 끝
		if (RoundsTransform[(CurRound - 1) % 10].IsEmpty()) { break; }
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		AFriendlyPawn* NewPawn = GetWorld()->SpawnActor<AFriendlyPawn>(AFriendlyPawn::StaticClass(), FTransform::Identity, ActorSpawnParameters);
		NewPawn->Species = PlayerPawnsInfo[i].Species;
		NewPawn->PawnGroup = PlayerPawnsInfo[i].PawnGroup;
		NewPawn->SetData();
		NewPawn->SetActorLocation(RoundsTransform[(CurRound - 1) % 10][i].GetLocation());
		//NewPawn->SetActorRotation(RoundsTransform[(CurRound - 1) % 10][i].GetRotation());
		//NewPawn->SetActorTransform(RoundsTransform[(CurRound - 1) % 10][i]);
		CurHavePawns.Add(NewPawn);
	}
}

void ABaseCharacter::OnFirstSet(uint8 Round)
{
	if (CurRound % 10 == 1)
	{
		SpawnPawn();
		CurRound++;
	}
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->SetFriendlyPawns(CurHavePawns);
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