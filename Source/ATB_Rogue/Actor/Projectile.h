// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Enums/PawnGroup.h"
#include "Projectile.generated.h"

UCLASS()
class ATB_ROGUE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetTargetActor(AActor* InTargetActor) { TargetActor = InTargetActor; }
	void SetParticleSystem(UParticleSystem* InParticleSystem) { ParticleSystem->SetTemplate(InParticleSystem); }
	void SetHitParticleSystem(UParticleSystem* InHitParticleSystem) { HitParticleSystem= InHitParticleSystem; }
	void SetTargetGroup(EPawnGroup Group);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	AActor* TargetActor;
	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UParticleSystemComponent* ParticleSystem;
	UParticleSystem* HitParticleSystem;
};
