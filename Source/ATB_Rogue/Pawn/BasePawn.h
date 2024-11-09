// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enums/Species.h"
#include "Enums/PawnGroup.h"

#include "Component/StatusComponent.h"
#include "Component/EffectComponent.h"
#include "Component/SkillComponent.h"
#include "Component/AnimComponent.h"
#include "Component/SplineCameraChildActorComponent.h"
#include "Component/BaseFloatingPawnMovement.h"
#include "Components/Slider.h"
#include "Components/TimelineComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DataTable.h"
#include "Data/PawnTableRow.h"

#include "BasePawn.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATBChanged, float, CurrentATB, float, MaxATB);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTurn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishTurn);

UCLASS()
class ATB_ROGUE_API ABasePawn : public APawn
{

	GENERATED_BODY()

public:

	friend class UBattleSubsystem;

	// Sets default values for this pawn's properties
	ABasePawn(const FObjectInitializer& ObjectInitializer);

	virtual void SetData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);

	virtual void ControllerInit();
	virtual void Init();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void ATBReset() { ATB_Cur = 0; }
	void ATBFeeling();

	void SetActive(bool Active) { bActive = Active; }
	void ActiveCollision(bool Active);

	void PlaySkillAnimation(ESkills UseSkill);
	void HitAnim();
	void Evolution();
	bool OnDieCheck();

	void MaterialInit();
	UFUNCTION()
	void OnDie();
	UFUNCTION()
	void OnSpawn();
	UFUNCTION()
	void OnDestroyEffect(float InDissolve);
	UFUNCTION()
	void OnDestroyEffectEnd();
	UFUNCTION()
	void OnSpawnEffect(float InDissolve);
	UFUNCTION()
	void OnSpawnEffectEnd();

public:
	UFUNCTION(BlueprintCallable)
	bool IsDie() { return bDie; }
	UFUNCTION(BlueprintCallable)
	bool IsDestroy() { return bDestroy; }

	bool IsActive() { return bActive; }

	float GetATB() { return ATB_Cur; }

	UFUNCTION(BlueprintCallable)
	float GetPercent() { return ATB_Cur / ATB_MAX; }

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetPortrait();

	TObjectPtr<USplineCameraChildActorComponent> GetCameraSpline() { return CameraSplineClass; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpecies Species;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPawnGroup PawnGroup;

public:
	//Test
	UDataTable* PawnDataTable;
	FPawnTableRow* PawnData;
	//

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UShapeComponent> CollisionComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBaseFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStatusComponent> StatusComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UEffectComponent> EffectComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkillComponent> SkillComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAnimComponent> AnimComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineCameraChildActorComponent> CameraSplineClass;

protected:
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DestroyEffectTimelineComponent;
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* SpawnEffectTimelineComponent;
	TArray<UMaterialInstanceDynamic*> MaterialInstanceDynamics;



public:
	void SetMaxHP(float InMaxHP) { MaxHP = InMaxHP; CurHP = MaxHP; }
	void SetATBSpeed(float InATBSpeed) {}
	void SetATBbar(USlider* InSlider) { ATBbar = InSlider; }
	USlider* GetATBbar() { return ATBbar; }
	UPROPERTY()
	USlider* ATBbar;

private:

	UPROPERTY(EditAnywhere)
	bool bActive = false;

	UPROPERTY(EditAnywhere)
	float ATB_Min = 0.f;
	UPROPERTY(EditAnywhere)
	float ATB_Cur = ATB_Min;
	UPROPERTY(EditAnywhere)
	float ATB_MAX = 1000.f;
	UPROPERTY(EditAnywhere)
	float ATB_Speed = 1.f;

	UPROPERTY(EditAnywhere)
	float MaxHP = 100;
	UPROPERTY(EditAnywhere)
	float CurHP = MaxHP;
	UPROPERTY(EditAnywhere)
	bool bDie = false;
	UPROPERTY(EditAnywhere)
	bool bDestroy = false;
	UPROPERTY()
	bool bEvolution = false;

public:
	UPROPERTY(BlueprintAssignable)
	FOnATBChanged OnATBChanged;
	UPROPERTY(BlueprintAssignable)
	FStartTurn StartTurn;
	UPROPERTY(BlueprintAssignable)
	FFinishTurn FinishTurn;
	UFUNCTION()
	virtual void OnStartBattle(uint8 Round);
	UFUNCTION()
	virtual void OnStartTurn();
	UFUNCTION()
	virtual void OnFinishTurn();
	UFUNCTION()
	virtual void OnBattleEndFirst();
private:
	void DrawRange(FVector CenterPoint, float Range, bool bPersistentLines = false);
};
