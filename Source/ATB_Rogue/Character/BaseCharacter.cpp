// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"


#include "Misc/Utils.h"

#include "Subsystem/BattleSubsystem.h"
#include "Pawn/FriendlySpawnLocation.h"
#include "Component/RotatorCharMoveComponent.h"
#include "Subsystem/ATBUserUISubSystem.h"
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
		//SpringArmComponent->bDoCollisionTest = false; //Temp
		SpringArmComponent->bEnableCameraRotationLag = true;
		SpringArmComponent->CameraRotationLagSpeed = 50.f;
		//SpringArmComponent->SetUsingAbsoluteRotation(false);
	}
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
		FTransform NewTransform = FTransform(FRotator(-30.f, 0.f, 0.f), FVector3d(0.f, 0.f, 800.f)); // 음 맵? 
		CameraComponent->SetRelativeTransform(NewTransform);
	}
	{
		PawnViewCameraComponent->SetupAttachment(RootComponent);
	}
	{
		UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
		CharacterMovementComponent->GravityScale = 0.f;
		
	}
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	bUseControllerRotationYaw = true;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController());
	////CameraViewMode
	//if (BasePlayerController->GetViewCameraMode() == ECameraViewMode::PawnView) { return; }

	//if (ActionPawn)
	//{
	//	ABaseAIController* ActionPawnController = Cast<ABaseAIController>(ActionPawn->GetController());
	//	float LerpSpeed = 5.0f;
	//	if (ActionPawnController->TargetPawn && BasePlayerController->GetViewCameraMode() == ECameraViewMode::Attack)
	//	{
	//		FVector StartVec = ActionPawn->GetActorLocation();
	//		FVector TargetVec = ActionPawnController->TargetPawn->GetActorLocation();
	//		FVector MiddleVec = (StartVec + TargetVec) * 0.5f;

	//		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), MiddleVec, DeltaTime, LerpSpeed);

	//		SetActorLocation(NewLocation);
	//	}
	//	else
	//	{
	//		//카메라 위치와 회전 보간
	//		FVector NewLocation = FMath::VInterpTo(GetActorLocation(), ActionPawn->GetActorLocation(), DeltaTime, LerpSpeed);
	//		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), ActionPawn->GetActorRotation(), DeltaTime, LerpSpeed);
	//		NewRotation.Roll = 0.f;

	//		SetActorLocationAndRotation(ActionPawn->GetActorLocation(), ActionPawn->GetActorRotation());
	//	}
	//}
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

	//CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//레벨 시작시 Instance 에서 폰정보를 받아옴
	{
		UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
		PlayerPawnsInfo = GameInstanceSubsystem->LoadPlayerPawnsInfo();
	}
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		BattleSubsystem->BattleStartFirst.AddDynamic(this, &ThisClass::OnFirstSet);
		BattleSubsystem->BattleEndSecond.AddDynamic(this, &ThisClass::OnBattleEndSecond);
	}
	Init();
}

void ABaseCharacter::Init()
{
	SetRoundsTransform(); 
	CurRound = 0;
}

void ABaseCharacter::SetRoundsTransform()
{
	TArray<AActor*> RoundTransforms;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AFriendlySpawnLocation::StaticClass(), FName("DefualtRound"), RoundTransforms);
	for (auto& Transforms : RoundTransforms)
	{
		AFriendlySpawnLocation* FriendlySpawnLocation = Cast<AFriendlySpawnLocation>(Transforms);
		RoundsTransform.Add(FriendlySpawnLocation->GetSpawnTransform());
	}
}


void ABaseCharacter::SpawnPawn()
{
	CurHavePawns.Empty();
	for (uint8 i = 0; i < PlayerPawnsInfo.Num(); i++)
	{
		if (PlayerPawnsInfo.IsEmpty()) { break; } //비었으면 끝
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		AFriendlyPawn* NewPawn = GetWorld()->SpawnActor<AFriendlyPawn>(AFriendlyPawn::StaticClass(), RoundsTransform[0][i], ActorSpawnParameters);
		NewPawn->Species = PlayerPawnsInfo[i].Species;
		NewPawn->PawnGroup = PlayerPawnsInfo[i].PawnGroup;
		//레벨이랑 베이스 스탯 세팅
		TSharedPtr<FSpeciesInfo> NewSpeciesInfo = PlayerPawnsInfo[i].SpeciesInfo;
		NewPawn->StatusComponent->SetSpeciesInfo(NewSpeciesInfo);
		//셋데이터에서 스탯은 베이스스탯만 초기화
		NewPawn->SetData();
		UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
		check(ATBUserUISubSystem);
		ATBUserUISubSystem->BattleUIAddPawn(NewPawn);
		NewPawn->SetActorTransform(RoundsTransform[0][i]);
		CurHavePawns.Add(NewPawn);
	}
}

void ABaseCharacter::OnFirstSet(uint8 Round)
{
	CurRound++;
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	if (CurRound % 10 == 1)
	{
		SpawnPawn(); //레벨 이동시 새로 생성
		BattleSubsystem->SetFriendlyPawns(CurHavePawns);
	}
	else //라운드 시작시 위치만 새로 조정
	{
		CurHavePawns = BattleSubsystem->FriendlyPawns;
		ReSetTransform();
	}
}

void ABaseCharacter::OnBattleEndSecond() //
{

}

void ABaseCharacter::ReSetTransform()
{
	for (uint8 i = 0; i < CurHavePawns.Num(); i++)
	{
		if (CurHavePawns.IsEmpty()) { break; } //비었으면 패스
		if (!IsValid(CurHavePawns[i])) { break; } //죽었으면 패스
		CurHavePawns[i]->SetActorTransform(RoundsTransform[0][i]);
	}
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