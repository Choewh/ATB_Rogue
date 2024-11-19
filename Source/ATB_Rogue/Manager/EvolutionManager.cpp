// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/EvolutionManager.h"
#include "LevelSequencePlayer.h"
#include "Subsystem/BattleSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/BasePlayerController.h"
#include "Character/BaseCharacter.h"
#include "Engine/SkinnedAssetCommon.h"
// Sets default values
AEvolutionManager::AEvolutionManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset = { TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrint/Input/EvolutionManager/IMC_Evolution.IMC_Evolution'") };
		check(Asset.Object);
		IMC_Evolution = Asset.Object;
	}
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));


		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		if (StaticMeshObject.Succeeded())
		{
			StaticMeshComponent->SetStaticMesh(StaticMeshObject.Object);
		}
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialObject(TEXT("/Script/Engine.Material'/Game/FX/EvolutionRoom.EvolutionRoom'"));
		if (MaterialObject.Succeeded())
		{
			StaticMeshComponent->SetMaterial(0, MaterialObject.Object);
		}
		StaticMeshComponent->SetRelativeScale3D(FVector(20.f, 20.f, 40.f));
	}
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

		EvolutionRoomEffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("EvolutionRoomEffectTimelineComponent"));

		FOnTimelineFloat Delegate;
		Delegate.BindDynamic(this, &ThisClass::OnEvolutionRoomEffect);
		EvolutionRoomEffectTimelineComponent->AddInterpFloat(CurveAsset.Object, Delegate);

		FOnTimelineEvent EndDelegate;
		EndDelegate.BindDynamic(this, &ThisClass::OnEvolutionRoomEffectEnd);
		EvolutionRoomEffectTimelineComponent->SetTimelineFinishedFunc(EndDelegate);
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
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEvolutionManager::BeginPlay()
{
	Super::BeginPlay();
	Init();
	{
		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		check(PlayerController);

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(IMC_Evolution, 0);
		EnableInput(PlayerController);

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		ensure(EnhancedInputComponent);

		if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Evolution, TEXT("IA_EvolutionSequenceStop")))
		{
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &AEvolutionManager::OnSequenceStop);
		}
	}

	{
		static UBattleSubsystem* BattleSubsystem = nullptr;
		BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		BattleSubsystem->OnEvolution.AddDynamic(this, &ThisClass::AddEvolutionPawn);
	}
	{
		ULevelSequence* LevelSequenceObject = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr, TEXT("/Game/Sequence/EvolutionLevelSequence.EvolutionLevelSequence")));
		if (LevelSequenceObject)
		{
			LevelSequence = LevelSequenceObject;// LevelSequence가 성공적으로 로드되었습니다.
		}
		/*static ConstructorHelpers::FObjectFinder<ULevelSequence> LS(TEXT("/Script/LevelSequence.LevelSequence'/Game/Sequence/EvolutionLevelSequence.EvolutionLevelSequence'"));
		if (LS.Succeeded())
		{
			LevelSequence = LS.Object;
		}*/

		FMovieSceneSequencePlaybackSettings Settings;
		Settings.bAutoPlay = false;
		Settings.bPauseAtEnd = true;
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, LevelSequenceActor);
		if (LevelSequenceObject)
			LevelSequencePlayer->OnFinished.AddDynamic(this, &ThisClass::OnSequenceFinished);

	}
}

// Called every frame
void AEvolutionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		if (!BattleSubsystem->PlayerController) { return; }
		if (BattleSubsystem->PlayerController->CheckBattleState(EBattleState::Evolution))
		{
			if (!EvolutionPawns.IsEmpty() && !LevelSequencePlayer->IsPlaying())
			{
				ESpecies EvolutioSpecies;
				if (EvolutionPawns.Dequeue(EvolutioSpecies))
					PlayEvolutionSequence(EvolutioSpecies);
			}
			else if (EvolutionPawns.IsEmpty() && !LevelSequencePlayer->IsPlaying())
			{
				BattleSubsystem->NextBattle();
			}
			else if (EvolutionPawns.IsEmpty() && LevelSequencePlayer->IsPlaying())
			{
				int a = 0;
			}
			else if (!EvolutionPawns.IsEmpty() && !LevelSequencePlayer->IsPlaying())
			{
				int b = 0;
			}
			else if (!EvolutionPawns.IsEmpty() && LevelSequencePlayer->IsPlaying())
			{
				int d = 0;
			}
		}
	}



}

void AEvolutionManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEvolutionManager::Init()
{
	UMaterialInterface* NewMaterial = StaticMeshComponent->GetMaterial(0);
	if (NewMaterial)
	{
		StaticMeshMaterialInstanceDynamics = UMaterialInstanceDynamic::Create(NewMaterial, this);
		StaticMeshComponent->SetMaterial(0, StaticMeshMaterialInstanceDynamics);
	}
}

void AEvolutionManager::AddEvolutionPawn(ESpecies AddSpecies)
{
	EvolutionPawns.Enqueue(AddSpecies);
}

void AEvolutionManager::PlayEvolutionSequence(ESpecies InSpecies)
{
	//Temp
	//시퀀스 안끝나는거 체크하기 
	SetData(InSpecies); //현재 Species , 다음 Species , 애니메이션 설정
	LevelSequencePlayer->Play();
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
	MaterialInit();
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
	DestroyEffectTimelineComponent->PlayFromStart();
	EvolutionRoomEffectTimelineComponent->PlayFromStart();
}

void AEvolutionManager::OnEvolutionRoomEffect(float InDissolve)
{
	StaticMeshMaterialInstanceDynamics->SetScalarParameterValue(TEXT("Amount"), InDissolve);
}

void AEvolutionManager::OnEvolutionRoomEffectEnd()
{
	EvolutionRoomEffectTimelineComponent->PlayFromStart();
}

void AEvolutionManager::OnDestroyEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	float Amount;
	for (int32 i = 0; i < MaterialNum; ++i)
	{

		MaterialInstanceDynamics[i]->GetScalarParameterValue(TEXT("Amount"), Amount);
		UE_LOG(LogTemp, Log, TEXT("%f"), Amount);
		UE_LOG(LogTemp, Log, TEXT("%f"), InDissolve);
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
	//EvolutionRoomEffectTimelineComponent->Stop();
}

void AEvolutionManager::OnSpawnEffect(float InDissolve)
{
	const int32 MaterialNum = MaterialInstanceDynamics.Num();
	float Amount;
	for (int32 i = 0; i < MaterialNum; ++i)
	{
		MaterialInstanceDynamics[i]->GetScalarParameterValue(TEXT("Amount"), Amount);
		UE_LOG(LogTemp, Log, TEXT("%f"), Amount);
		UE_LOG(LogTemp, Log, TEXT("%f"), InDissolve);
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
	EvolutionRoomEffectTimelineComponent->Stop();
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
void AEvolutionManager::OnSequenceFinished()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(PlayerController);
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Character);
	if (BasePlayerController && BasePlayerController->DefaultCamera)
	{
		BasePlayerController->SetViewTarget(BaseCharacter);
		UE_LOG(LogTemp, Log, TEXT("시네마틱 카메라에서 기본 카메라로 전환되었습니다."));
	}
}

void AEvolutionManager::OnSequenceStop(const FInputActionValue& InputActionValue)
{
	if (LevelSequencePlayer->IsPlaying())
	{
		LevelSequencePlayer->GoToEndAndStop();
		OnSequenceFinished();
	}
}
