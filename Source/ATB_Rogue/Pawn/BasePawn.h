// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Data/PawnTableRow.h"
#include "Enums/Species.h"
#include "Enums/PawnGroup.h"

#include "Component/StatusComponent.h"
#include "Component/EffectComponent.h"
#include "Component/SplineCameraChildActorComponent.h"
#include "Component/BaseFloatingPawnMovement.h"
#include "Components/Slider.h"
#include "Components/BoxComponent.h"



#include "BasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATBChanged, float, CurrentATB, float, MaxATB);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMove, FVector, MovePoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHideEffect);

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
public:

	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual bool BattleStart();
	virtual void TurnEnd();
	void ABTReset() { ABT_Cur = 0; }
	void ABTFeeling();	
	bool Movealbe(FVector NewDestination);
	void MakeViewMoveRange();
	void HideMoveRange();
	void MoveTo(FVector NewDestination);
	void SetActive(bool Active) { bActive = Active; }


public:

	bool IsActive() { return bActive; }

	float GetABT() { return ABT_Cur; }

	UFUNCTION(BlueprintCallable)
	float GetPercent() { return ABT_Cur / ABT_MAX; }

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
	TObjectPtr<USplineCameraChildActorComponent> CameraSplineClass;

	void SetATBbar(USlider* InSlider) {ATBbar = InSlider;}
	USlider* GetABTbar() { return ATBbar; }
	UPROPERTY()
	USlider* ATBbar;

private:

	UPROPERTY(EditAnywhere)
	bool bActive = true;

	UPROPERTY(EditAnywhere)
	float ABT_Min = 0.f;
	UPROPERTY(EditAnywhere)
	float ABT_Cur = ABT_Min;
	UPROPERTY(EditAnywhere)
	float ABT_MAX = 1000.f;
	UPROPERTY(EditAnywhere)
	float ABT_Speed = 1.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnATBChanged OnATBChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMove OnMove;
	UPROPERTY(BlueprintAssignable)
	FHideEffect HideEffect;
private:
	void DrawRange(FVector CenterPoint, float Range, bool bPersistentLines = false);
};
