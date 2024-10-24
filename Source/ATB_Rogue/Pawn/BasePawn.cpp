// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BasePawn.h"
#include "DrawDebugHelpers.h"

#include "Misc/Utils.h"
#include "Widget/ABTBarUserWidget.h"
#include "Subsystem/BattleSubsystem.h"
#include "AI/BaseAIController.h"

#include "Subsystem/ActorpoolSubsystem.h"

// Sets default values
ABasePawn::ABasePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//폰 데이터 테이블 초기화
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> PawnDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/PawnTableRow.PawnTableRow'"));
		if (PawnDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			PawnDataTable = PawnDataObject.Object;
		}
	}
	{
		DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
		RootComponent = DefaultSceneRoot;

		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	{
		MovementComponent = CreateDefaultSubobject<UBaseFloatingPawnMovement>(TEXT("BaseFloatingPawnMovement"));
		StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		EffectComponent = CreateDefaultSubobject<UEffectComponent>(TEXT("EffectComponent"));
	}
	{
		CameraSplineClass = CreateDefaultSubobject<USplineCameraChildActorComponent>(TEXT("CameraSpline"));
		CameraSplineClass->SetupAttachment(RootComponent);
	}
}


// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	SetData(); //인자가 굳이 필요하진 않지만 복붙하기 편하게 넣음	
}
//서브게임인스턴스에 추가 - > 배틀시작트리거 -> 배틀시작시 배열추가
void ABasePawn::SetData()
{
	TArray<FPawnTableRow*> PawnTable_Array;
	PawnDataTable->GetAllRows<FPawnTableRow>("", PawnTable_Array);

	if (!PawnData || PawnData->Species != Species)
	{
		for (auto& PawnTable : PawnTable_Array)
		{
			if (PawnTable->Species == Species)
			{
				PawnData = PawnTable;
				break;
			}
		}
	}

	AIControllerClass = PawnData->AIController;

	if (PawnData)
	{
		if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != PawnData->CollisionClass)
		{
			EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
			CollisionComponent = NewObject<UShapeComponent>(this, PawnData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
			CollisionComponent->RegisterComponent();
			CollisionComponent->SetCollisionProfileName(TEXT("Enemy"));
			//CollisionComponent->SetCollisionProfileName(TEXT("NoCollision"));
			CollisionComponent->SetCanEverAffectNavigation(false);
			SetRootComponent(CollisionComponent);
			DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
			DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
			UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent);
			BoxComponent->SetBoxExtent(PawnData->CollisionBoxExtent);
		}
		SkeletalMeshComponent->SetSkeletalMesh(PawnData->SkeletalMesh);
		SkeletalMeshComponent->SetAnimClass(PawnData->AnimClass);
		SkeletalMeshComponent->SetRelativeTransform(PawnData->MeshTransform);;
		CameraSplineClass->SetData(PawnData->CameraSplineClass);
	}
	if (StatusComponent)
	{
		StatusComponent->SetData(Species);

		ABT_Speed = StatusComponent->GetStat(EStat::SPD);
	}

	if (EffectComponent)
	{
		EffectComponent->SetData(Species);
	}
}

void ABasePawn::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData();
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
	SetData();
	SetActorTransform(Transform);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABTFeeling();

}

bool ABasePawn::BattleStart()
{

	return true;

}

void ABasePawn::TurnEnd()
{
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	BattleSubsystem->FinishTurn();
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
	}
	OnATBChanged.Broadcast(ABT_Cur, ABT_MAX);
}
bool ABasePawn::Movealbe(FVector NewDestination)
{
	//폰과 목표 사이거리 계산
	FVector CenterPoint = GetActorLocation();
	float Distance;
	Distance = FVector::Dist(CenterPoint, NewDestination);

	if (Distance <= StatusComponent->GetMoveRange()) {
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
void ABasePawn::MakeViewMoveRange()
{
	//이동사거리 표시
	if (!EffectComponent) { ensure(false); return; }

	EffectComponent->ViewMoveRange(GetActorLocation(), StatusComponent->GetMoveRange());

}
void ABasePawn::HideMoveRange()
{
	if (!EffectComponent) { ensure(false); return; }
	EffectComponent->DeViewMoveRange();
}
// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
void ABasePawn::MoveTo(FVector NewDestination)
{

	//지금은 그냥 셋로케이션으로 로직 확인만 ㅇ
	//if (GetController() && GetController()->IsValidLowLevel())

	HideMoveRange();
	OnMove.Broadcast(NewDestination);
	// AI 컨트롤러가 활성화되어 있습니다.
//SetActorLocation(NewDestination);
// 알아서 체크 일정거리 이상 가까워지면 멈추고 트루 반환
}

UTexture2D* ABasePawn::GetPortrait()
{
	if (PawnData) return PawnData->Portraits;
	return nullptr;
}

void ABasePawn::DrawRange(FVector CenterPoint, float Range, bool bPersistentLines)
{
	// 범위의 색상과 선 두께 설정
	FColor SphereColor = FColor::Green;
	float Duration = 0.0f; // 영구적으로 표시하려면 0으로 설정

	// 구체를 그립니다.
	DrawDebugSphere(GetWorld(), CenterPoint, Range, 12, SphereColor, bPersistentLines, Duration);
}

