// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EvolutionManager.h"
#include "LevelSequencePlayer.h"
#include "Engine/SkinnedAssetCommon.h"
// Sets default values
AEvolutionManager::AEvolutionManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> PawnDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/PawnTableRow.PawnTableRow'"));
		if (PawnDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			PawnDataTable = PawnDataObject.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UDataTable> AnimDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/AnimTableRow.AnimTableRow'"));
		if (AnimDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			AnimDataTable = AnimDataObject.Object;
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

		DestroyEffectTimelineComponent->SetPlayRate(0.5f);
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

		SpawnEffectTimelineComponent->SetPlayRate(0.5f);
	}

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneComponent;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEvolutionManager::BeginPlay()
{
	Super::BeginPlay();
	PlayEvolutionSequence(ESpecies::Guilmon); //현재 Species 받고
}

// Called every frame
void AEvolutionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 0 에서 0 으로
	// 
}

void AEvolutionManager::PlayEvolutionSequence(ESpecies InSpecies)
{
	//Temp
	SetData(InSpecies); //현재 Species , 다음 Species , 애니메이션 설정
	//Play
}

void AEvolutionManager::SetData(ESpecies InSpecies)
{
	TArray<FPawnTableRow*> PawnTable_Array;
	PawnDataTable->GetAllRows<FPawnTableRow>("", PawnTable_Array);

	if (InSpecies == ESpecies::None) { return; }

	for (auto& PawnTable : PawnTable_Array)
	{
		if (PawnTable->Species == InSpecies)
		{
			PawnData = PawnTable;
			break;
		}
	}

	{
		SkeletalMeshComponent->SetSkeletalMesh(PawnData->SkeletalMesh);
		SkeletalMeshComponent->SetAnimClass(PawnData->AnimClass);
		SkeletalMeshComponent->SetRelativeTransform(PawnData->MeshTransform);
	}

	ESpecies NextSpecies = PawnData->NextSpecies;

	if (NextSpecies == ESpecies::End) { return; }

	for (auto& PawnTable : PawnTable_Array)
	{
		if (PawnTable->Species == NextSpecies)
		{
			PawnData = PawnTable;
			break;
		}
	}

	TArray<FAnimMontageTableRow*> AnimTable_Array;
	AnimDataTable->GetAllRows<FAnimMontageTableRow>("", AnimTable_Array);

	for (auto& AnimTable : AnimTable_Array)
	{
		if (AnimTable->Species == NextSpecies)
		{
			AnimData = AnimTable;
		}
	}
	MaterialInit();
}

void AEvolutionManager::EvolutionAnimation()
{
	//UI 가리기
	StartEvolution();
}

void AEvolutionManager::UpdateEvolutionPawnMesh()
{
	SkeletalMeshComponent->SetSkeletalMesh(PawnData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(PawnData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(PawnData->MeshTransform);
}

void AEvolutionManager::StartEvolution()
{
	DestroyEffectTimelineComponent->Play();
}
void AEvolutionManager::OnDestroyEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(TEXT("Amount"), InDissolve);
	}
}

void AEvolutionManager::OnDestroyEffectEnd()
{
	UpdateEvolutionPawnMesh();
	OnSpawn();
}
/// <summary>
/// Spawn
/// </summary>
void AEvolutionManager::OnSpawn()
{
	MaterialInit();
	SpawnEffectTimelineComponent->PlayFromStart();
}

void AEvolutionManager::OnSpawnEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->SetScalarParameterValue(TEXT("Amount"), InDissolve);
	}
}
void AEvolutionManager::OnSpawnEffectEnd()
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	// 이전 델리게이트 해제
	AnimInstance->OnMontageEnded.Clear();
	// 몽타주가 끝났을 때 호출될 함수 바인딩
	AnimInstance->OnMontageEnded.AddDynamic(this, &AEvolutionManager::OnMontageEnded);
	AnimInstance->Montage_Play(AnimData->EvoReactMontage);
}
void AEvolutionManager::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 델리게이트 해제 (한 번만 호출되도록 보장)
	//필요한가? 일단 냅두기
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if (AnimInstance)
	{
		//UI 보여주기
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &AEvolutionManager::OnMontageEnded);
	}
}

void AEvolutionManager::MaterialInit()
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