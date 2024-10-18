// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BasePawn.h"
#include "DrawDebugHelpers.h"
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

	//SplineCameraChildActorComponent
	{
		CameraSplineClass = CreateDefaultSubobject<USplineCameraChildActorComponent>(TEXT("CameraSpline"));
		CameraSplineClass->SetupAttachment(RootComponent);
	}
}

void ABasePawn::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = DataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Pawn")); // << 임시로 이렇게 쓰고있는데 수정해야함
	if (!Data) { ensure(false); return; }

	EnemyData = Data;

	{
		SkeletalMeshComponent->SetSkeletalMesh(EnemyData->SkeletalMesh);
		SkeletalMeshComponent->SetAnimClass(EnemyData->AnimClass);
		SkeletalMeshComponent->SetRelativeTransform(EnemyData->MeshTransform);
	}
	{
		CameraSpline = EnemyData->CameraSpline;
	}
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->EntryEnemy(this);
	SetData(DataTableRowHandle);
}

void ABasePawn::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		SetData(DataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void ABasePawn::PostLoad()
{
	Super::PostLoad();
}

void ABasePawn::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void ABasePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABasePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
	SetActorTransform(Transform);
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
		BattleSubsystem->EnterActiveTurn(this);
	}
	else
	{
		ABT_Cur += ABT_Speed;
		//뷰포트 로그 float->string
		FString LogMessage = FString::Printf(TEXT("%f"), ABT_Cur);
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
	}
}
bool ABasePawn::Movealbe(FVector NewDestination)
{
	FVector CenterPoint = GetActorLocation();

	float Range = 1000.0f; // 설정한 범위 폰데이터를 받아와야함 배틀시스템에서 읽어오는걸 만들기?

	float Distance = FVector::Dist(CenterPoint, NewDestination);

	if (Distance <= Range) {
		// 범위 내에 있는 경우
		UE_LOG(LogTemp, Warning, TEXT("Target is within range."));
		return true;
	}
	else {
		// 범위 밖인 경우
		UE_LOG(LogTemp, Warning, TEXT("Target is out of range."));
		return false;
	}
}
// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
bool ABasePawn::MoveTo(FVector NewDestination)
{
	//지금은 그냥 셋로케이션으로 로직 확인만 ㅇ
	SetActorLocation(NewDestination);
	return true;


	// 알아서 체크 일정거리 이상 가까워지면 멈추고 트루 반환
}

void ABasePawn::DrawRange(FVector CenterPoint, float Range, bool bPersistentLines)
{
		// 범위의 색상과 선 두께 설정
		FColor SphereColor = FColor::Green;
		float Duration = 0.0f; // 영구적으로 표시하려면 0으로 설정

		// 구체를 그립니다.
		DrawDebugSphere(GetWorld(), CenterPoint, Range, 12, SphereColor, bPersistentLines , Duration);
}

