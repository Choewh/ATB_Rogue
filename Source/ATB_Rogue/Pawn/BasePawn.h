// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class ATB_ROGUE_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void ABTFeeling();

	void MoveTo();

	void SetActive(bool Active) { bActive = Active; }

public:

	bool IsActive() { return bActive; }

	float GetABT() { return ABT_Cur; }

private:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayController;
	UPROPERTY()
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

private:


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


};
