// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/BasePawn.h"
#include "DrawDebugHelpers.h"

#include "Misc/Utils.h"
#include "Widget/ATBBarUserWidget.h"
#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/ATBUserUISubSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/SkinnedAssetCommon.h"
#include "Subsystem/DataSubsystem.h"
#include "Subsystem/ActorpoolSubsystem.h"

class UBattleSubsystem;

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
		static ConstructorHelpers::FObjectFinder<UCurveFloat>CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/BluePrint/Component/CV_02Curve.CV_02Curve'"));
		check(CurveAsset.Object);

		DestroyEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("OnDestroyEffectTimelineComponent"));

		FOnTimelineFloat Delegate;
		Delegate.BindDynamic(this, &ThisClass::OnDestroyEffect);
		DestroyEffectTimelineComponent->AddInterpFloat(CurveAsset.Object, Delegate);

		FOnTimelineEvent EndDelegate;
		EndDelegate.BindDynamic(this, &ThisClass::OnDestroyEffectEnd);
		DestroyEffectTimelineComponent->SetTimelineFinishedFunc(EndDelegate);
	}
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat>CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/BluePrint/Component/CV_20Curve.CV_20Curve'"));
		check(CurveAsset.Object);

		SpawnEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpawnEffectTimelineComponent"));

		FOnTimelineFloat Delegate;
		Delegate.BindDynamic(this, &ThisClass::OnSpawnEffect);
		SpawnEffectTimelineComponent->AddInterpFloat(CurveAsset.Object, Delegate);

		FOnTimelineEvent EndDelegate;
		EndDelegate.BindDynamic(this, &ThisClass::OnSpawnEffectEnd);
		SpawnEffectTimelineComponent->SetTimelineFinishedFunc(EndDelegate);
	}
	{
		DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
		RootComponent = DefaultSceneRoot;

		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SkeletalMeshComponent->bReceivesDecals = false;
	}
	{
		MovementComponent = CreateDefaultSubobject<UBaseFloatingPawnMovement>(TEXT("BaseFloatingPawnMovement"));
		StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		EffectComponent = CreateDefaultSubobject<UEffectComponent>(TEXT("EffectComponent"));
		SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
		AnimComponent = CreateDefaultSubobject<UAnimComponent>(TEXT("AnimComponent"));
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
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::OnStartBattle);

		BattleSubsystem->BattleStartTurn.AddDynamic(this, &ThisClass::OnStartTurn);
		BattleSubsystem->BattleFinishTurn.AddDynamic(this, &ThisClass::OnFinishTurn);

		BattleSubsystem->BattleEndFirst.AddDynamic(this, &ThisClass::OnBattleEndFirst);
	}
}
void ABasePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


	UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
	check(ATBUserUISubSystem);
	ATBUserUISubSystem->BattleUIRemovePawn(this);
}
//서브게임인스턴스에 추가 - > 배틀시작트리거 -> 배틀시작시 배열추가
void ABasePawn::SetData()
{
	
	PawnData = GetGameInstance()->GetSubsystem<UDataSubsystem>()->GetDataTableRow<FPawnTableRow>(EDataTableType::Pawn,Species);

	{
		if (PawnGroup == EPawnGroup::Enemy)
		{
			AIControllerClass = PawnData->EnemyAIController;

		}
		else if (PawnGroup == EPawnGroup::Friendly)
		{
			AIControllerClass = PawnData->FriendlyAIController;
		}
	}

	if (PawnData)
	{
		if (!IsValid(CollisionComponent) || PawnData->CollisionClass)
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
			UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent);
			CapsuleComponent->SetCapsuleSize(PawnData->CollisionCapsuleRadius, PawnData->CollisionCapsuleHalfHeight);
			CapsuleComponent->SetWorldRotation(FQuat::Identity);
			CapsuleComponent->bReceivesDecals = false;
			MovementComponent->UpdateNavAgent(*CapsuleComponent);
		}
		SkeletalMeshComponent->SetSkeletalMesh(PawnData->SkeletalMesh);
		SkeletalMeshComponent->SetAnimClass(PawnData->AnimClass);
		SkeletalMeshComponent->SetRelativeTransform(PawnData->MeshTransform);
		CameraSplineClass->SetRelativeTransform(PawnData->MeshTransform);
		CameraSplineClass->SetData(PawnData->CameraSplineClass);
		MovementComponent->SetUpdatedComponent(RootComponent);
	}
	if (StatusComponent)
	{
		StatusComponent->SetData(Species);
		//HP 계산
		if (MaxHP == CurHP)
		{
			SetMaxHP(FMath::RoundToInt(((StatusComponent->GetSpeciesInfo()->HP * static_cast<uint8>(StatusComponent->GetSpeciesInfo()->Stage) + 100.f) * ((StatusComponent->GetSpeciesInfo()->Level / 100.f)) + 10.f)));
		}

		ATB_Speed = StatusComponent->GetSpeciesInfo()->SPD;
	}

	if (EffectComponent)
	{
		EffectComponent->SetData(Species);
	}

	if (SkillComponent)
	{
		SkillComponent->SetData(Species);
	}

	if (AnimComponent)
	{
		AnimComponent->SetData(Species);
	}
	MaterialInit();
}

void ABasePawn::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
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
}

void ABasePawn::ControllerInit(bool Active)
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(GetController());
	BaseAIController->SetActiveTurn(Active);
}

void ABasePawn::Init()
{
	ATBReset();
	bActive = false;
	bDie = false;
	bDestroy = false;
	bEvolution = false;
	OnChangedHPBar.Broadcast(this, CurHP / MaxHP);
	MovementComponent->SetUseControllerRotationYaw(true);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATBFeeling();

}

void ABasePawn::ATBFeeling()
{
	if (!bActive)
	{
		return;
	}

	if (ATB_Cur >= ATB_MAX)
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->EnterActiveTurn(this);
	}
	else
	{
		ATB_Cur += ATB_Speed;
		//뷰포트 로그 float->string
	}
	OnChangedATBBar.Broadcast(this, ATB_Cur / ATB_MAX);
}


void ABasePawn::ActiveCollision(bool Active)
{
	CollisionComponent->SetCanEverAffectNavigation(Active);
	SetCanAffectNavigationGeneration(Active);
}

void ABasePawn::PlaySkillAnimation(ESkills UseSkill)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	switch (UseSkill)
	{
	case ESkills::None:
		return;
	case ESkills::FirstSkill:
		AnimInstance->Montage_Play(SkillComponent->FirstSkillData->SkillReactMontage);
		break;
	case ESkills::SecondSkill:
		AnimInstance->Montage_Play(SkillComponent->SecondSkillData->SkillReactMontage);
		break;
	case ESkills::ThirdSkill:
		AnimInstance->Montage_Play(SkillComponent->ThirdSkillData->SkillReactMontage);
		break;
	default:
		break;
	}
}

void ABasePawn::HitAnim()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	AnimInstance->Montage_Play(AnimComponent->AnimData->HitReactMontage);
}

float ABasePawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDie()) { return 0.f; }
	//아래에서 최종데미지 계산
	float DamageResult = FMath::FloorToInt(StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser));
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	CurHP -= DamageResult;
	CurHP = FMath::Clamp(CurHP, 0.f, CurHP);
	OnChangedHPBar.Broadcast(this, CurHP / MaxHP);
	if (CurHP == 0.f)
	{	//플래그 변경
		bDie = true;
	}
	//체력바 깍이는 연출 ㄱ

	return 0.0f;
}

void ABasePawn::Evolution()
{
	Species = PawnData->NextSpecies;
	if (Species != ESpecies::End)
	{
		bEvolution = true;
		int Pre_MaxHP = MaxHP;
		int Pre_CurHP = CurHP;
		SetData();
		Pre_MaxHP = MaxHP - Pre_MaxHP;
		CurHP = Pre_CurHP + Pre_MaxHP;

		UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
		check(ATBUserUISubSystem);
		ATBUserUISubSystem->UpdatePawnUI(this);
		OnChangedHPBar.Broadcast(this, CurHP / MaxHP);
	}
}

bool ABasePawn::OnDieCheck()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (bDie)
	{
		AnimInstance->Montage_Play(AnimComponent->AnimData->DieReactMontage);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"), 1.f, false);
		return true;
	}
	return false;
}
/// <summary>
/// GetInfo
/// </summary>
UTexture2D* ABasePawn::GetPortrait()
{
	if (PawnData) return PawnData->Portraits;
	return nullptr;
}

/// <summary>
/// Delegate
/// </summary>
void ABasePawn::OnStartBattle(uint8 Round)
{
	Init();
}
void ABasePawn::OnStartTurn()
{
	bActive = false;
	MovementComponent->SetUseControllerRotationYaw(true);
}

void ABasePawn::OnFinishTurn()
{
	UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
	check(ATBUserUISubSystem);
	ATBUserUISubSystem->UpdatePawnUI(GetOwner());
	ActiveCollision(true);
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(GetController());
	BaseAIController->SetActiveTurn(false);
	MovementComponent->SetUseControllerRotationYaw(false);
	bActive = true;
}
void ABasePawn::OnBattleEndFirst(uint16 Exp) //Temp 레벨업 넣어뒀는데 TODO 경험치량 설정하기
{
	StatusComponent->GetLevelExp(Exp);
	
	Init();

	UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
	check(ATBUserUISubSystem);
	ATBUserUISubSystem->UpdatePawnUI(GetOwner());
}
void ABasePawn::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//에볼루션 매니저로 옮겨줬음
	
	//// Evolution 상태일 때만 BattleState를 설정
	//if (bEvolution)
	//{
	//	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	//	if (BattleSubsystem)
	//	{
	//		BattleSubsystem->SetBattleState(EBattleState::Default);
	//	}
	//	bEvolution = false;
	//}

	//// 델리게이트 해제 (한 번만 호출되도록 보장)
	//UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	//if (AnimInstance)
	//{
	//	AnimInstance->OnMontageEnded.RemoveDynamic(this, &ABasePawn::OnMontageEnded);
	//}
}
/// <summary>
/// EffectTimeLine
/// </summary>
void ABasePawn::MaterialInit()
{
	MaterialInstanceDynamics.Empty();
	const int32 MaterialNum = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials().Num();
	MaterialInstanceDynamics.Reserve(MaterialNum);
	const TArray<FSkeletalMaterial> SkeletalMaterials = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials();

	for (int32 i = 0; i < MaterialNum; ++i)
	{
		UMaterialInterface* OriginalMaterial = SkeletalMaterials[i].MaterialInterface;
		if (OriginalMaterial)
		{
			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
			MaterialInstanceDynamics.Add(DynamicMaterial);

			SkeletalMeshComponent->SetMaterial(i, DynamicMaterial);
		}
	}
}
/// <summary>
/// Die
/// </summary>
void ABasePawn::OnDie()
{
	DestroyEffectTimelineComponent->Play();
}
void ABasePawn::OnDestroyEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(TEXT("Amount"), InDissolve);
	}
}

void ABasePawn::OnDestroyEffectEnd()
{
	//bDie
	bDestroy = true;
}
/// <summary>
/// Spawn
/// </summary>
void ABasePawn::OnSpawn()
{
	SpawnEffectTimelineComponent->PlayFromStart();
}

void ABasePawn::OnSpawnEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(TEXT("Amount"), InDissolve);
	}
}
void ABasePawn::OnSpawnEffectEnd()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	// 이전 델리게이트 해제
	AnimInstance->OnMontageEnded.Clear();
	// 몽타주가 끝났을 때 호출될 함수 바인딩
	AnimInstance->OnMontageEnded.AddDynamic(this, &ABasePawn::OnMontageEnded);
	if (bEvolution)
	{
		AnimInstance->Montage_Play(AnimComponent->AnimData->EvoReactMontage);
		//UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		//BattleSubsystem->SetBattleState(EBattleState::Default);
	}
	else
	{
		AnimInstance->Montage_Play(AnimComponent->AnimData->RoarReactMontage);
	}
}
/// <summary>
/// Debug
/// </summary>