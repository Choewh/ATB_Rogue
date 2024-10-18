// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "Actor/BaseCameraSplineActor.h"
#include "Pawn/BasePawn.h"
#include "PawnViewCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UPawnViewCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	UPawnViewCameraComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION()
	void OnPawnViewCamera(ABasePawn* ViewEnemy);

	bool SetView(bool View) { bView = View; if(!View)CameraSplineTimelineComponent->Stop(); return bView; }

	bool isView() { return bView; }

	UFUNCTION()
	void StartSplineMoving(float InDissolve);

private:
	bool bView = false;

public:
	UPROPERTY()
	UTimelineComponent* CameraSplineTimelineComponent;
};
