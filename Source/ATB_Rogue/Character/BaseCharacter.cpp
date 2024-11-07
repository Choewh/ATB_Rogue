// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"


#include "Misc/Utils.h"

#include "Subsystem/BattleSubsystem.h"
#include "Pawn/FriendlySpawnLocation.h"
#include "Component/RotatorCharMoveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

class ABasePlayerController;

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URotatorCharMoveComponent>(Super::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//bOrientRotationToMovement = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PawnViewCameraComponent = CreateDefaultSubobject<UPawnViewCameraComponent>(TEXT("PawnViewCamera"));
	{
		SpringArmComponent->SetupAttachment(GetMesh());
		SpringArmComponent->TargetArmLength = 1500.f;
		SpringArmComponent->ProbeSize = 5.0;
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritPitch = false;
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
	bUseControllerRotationYaw = false;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController());
	//CameraViewMode
	if (BasePlayerController->GetViewCameraMode() == ECameraViewMode::PawnView) { return; }

	if (ActionPawn)
	{
		ABaseAIController* ActionPawnController = Cast<ABaseAIController>(ActionPawn->GetController());
		float LerpSpeed = 3.0f;
		if (ActionPawnController->TargetPawn && BasePlayerController->GetViewCameraMode() == ECameraViewMode::Attack)
		{
			FVector StartVec = ActionPawn->GetActorLocation();
			FVector TargetVec = ActionPawnController->TargetPawn->GetActorLocation();
			FVector MiddleVec = (StartVec + TargetVec) * 0.5f;

			FVector NewLocation = FMath::VInterpTo(GetActorLocation(), MiddleVec, DeltaTime, LerpSpeed);

			SetActorLocation(NewLocation);
		}
		else
		{
			//카메라 위치와 회전 보간
			FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ActionPawn->GetActorLocation(), DeltaTime, LerpSpeed);
			FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), ActionPawn->GetActorRotation(), DeltaTime, LerpSpeed);
			NewRotation.Pitch = 0.f;
			SetActorLocationAndRotation(NewLocation, NewRotation);
		}
		//카메라의 회전 액션폰이 바라보는 방향 뒤에 서게 함
		FVector StartVec = GetActorLocation();
		FVector TargetVec = ActionPawn->GetActorForwardVector();

		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);

		// 최종 회전 적용
		SetActorRotation(LookAtRotator);
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Controller == nullptr)
	{
		Controller = GetWorld()->SpawnActor<ABasePlayerController>(ABasePlayerController::StaticClass());
		Controller->Possess(this);
	}

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

		BattleSubsystem->BattleStartTurn.AddDynamic(this, &ThisClass::OnStartTurn);
		BattleSubsystem->BattleFinishTurn.AddDynamic(this, &ThisClass::OnFinishTurn);
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
		NewPawn->SetSpawnPos(RoundsTransform[(CurRound - 1) % 10][i].GetRotation().GetForwardVector());
		NewPawn->OnSpawn();
		CurHavePawns.Add(NewPawn);
	}
}

void ABaseCharacter::OnStartTurn()
{
	ABasePawn* Pawn = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn();
	if (Pawn)
	{
		ActionPawn = Pawn;
	}
}
void ABaseCharacter::OnFinishTurn()
{
	if (ActionPawn)
	{
		ActionPawn = nullptr;
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

	//if (Controller == nullptr)
	//{
	//	Controller = GetWorld()->SpawnActor<ABasePlayerController>(ABasePlayerController::StaticClass());
	//	Controller->Possess(this);
	//}

	//CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	////레벨 시작시 Instance 에서 폰정보를 받아옴
	//{
	//	UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
	//	PlayerPawnsInfo = GameInstanceSubsystem->GetPlayerPawnsInfo();
	//}
	//{
	//	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	//	check(BattleSubsystem);
	//	BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);

	//	BattleSubsystem->BattleStartTurn.AddDynamic(this, &ThisClass::OnStartTurn);
	//	BattleSubsystem->BattleFinishTurn.AddDynamic(this, &ThisClass::OnFinishTurn);
	//}
	//Init();
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