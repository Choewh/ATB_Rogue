// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Data/DataTableRows.h"
#include "Component/SplineCameraChildActorComponent.h"

#include "BasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATBChanged, float, CurrentATB, float, MaxATB);

UCLASS()
class ATB_ROGUE_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void ABTReset() { ABT_Cur = 0; }

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	float GetCurATBPercent() { return ABT_Cur / ABT_MAX; }
	void ABTFeeling();
	void MoveTo(FVector NewDestination);
	void SetActive(bool Active) { bActive = Active; }


public:

	bool IsActive() { return bActive; }

	float GetABT() { return ABT_Cur; }

	TObjectPtr<USplineCameraChildActorComponent> GetCameraSpline() { return CameraSplineClass; }

private:

	UPROPERTY()
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ATB_ROGUE.PawnTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FPawnTableRow* EnemyData;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineCameraChildActorComponent> CameraSplineClass;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseCameraSplineActor> CameraSpline;

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

private:
	void DrawRange(FVector CenterPoint, float Range, bool bPersistentLines = false);
};
