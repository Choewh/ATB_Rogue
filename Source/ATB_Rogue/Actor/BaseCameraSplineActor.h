// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "BaseCameraSplineActor.generated.h"

UCLASS()
class ATB_ROGUE_API ABaseCameraSplineActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseCameraSplineActor();

	USplineComponent* GetPaths() { return SplineComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	APawn* OwningPawn = nullptr;

	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComponent;

};
