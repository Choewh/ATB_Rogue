// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pawn/FriendlyPawn.h"
#include "Subsystem/EnemyCreateSubsystem.h"
#include "Camera/PawnViewCameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "BaseCharacter.generated.h"

UCLASS()
class ATB_ROGUE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime)override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)override;

	virtual void Init();
	virtual void SetRoundsTransform();

public:
	UFUNCTION()
	virtual void SpawnPawn(); 

	UFUNCTION()
	virtual void OnFirstSet(uint8 Round);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnViewCameraComponent* PawnViewCameraComponent;


	TArray<FBasePawnInfo> PlayerPawnsInfo;
protected:
	TArray<ABasePawn*> CurHavePawns;
	TArray<TArray<FTransform>> RoundsTransform; 
private:
	uint8 CurRound = 1;
};
