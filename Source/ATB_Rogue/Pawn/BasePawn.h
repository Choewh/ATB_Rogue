// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Engine/DataTable.h"
#include "Data/PawnTableRow.h"
#include "Enums/Species.h"

#include "Component/StatusComponent.h"
#include "Component/SplineCameraChildActorComponent.h"

#include "BasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATBChanged, float, CurrentATB, float, MaxATB);

UCLASS()
class ATB_ROGUE_API ABasePawn : public APawn
{
	GENERATED_BODY()


public:

	friend class UBattleSubsystem;

	// Sets default values for this pawn's properties
	ABasePawn();
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void ABTReset() { ABT_Cur = 0; }

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	float GetCurATBPercent() { return ABT_Cur / ABT_MAX; }
	void ABTFeeling();
	bool Movealbe(FVector NewDestination);
	void MakeViewMoveRange();
	
	bool MoveTo(FVector NewDestination);
	void SetActive(bool Active) { bActive = Active; }


public:

	bool IsActive() { return bActive; }

	float GetABT() { return ABT_Cur; }

	TObjectPtr<USplineCameraChildActorComponent> GetCameraSpline() { return CameraSplineClass; }

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpecies Species; // 디지몬 종

protected:
	//Test
	UDataTable* PawnDataTable;
	FPawnTableRow* PawnData;
	//

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineCameraChildActorComponent> CameraSplineClass;

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
