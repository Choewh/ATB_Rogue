// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile.h"
#include "Pawn/BasePawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->InitialSpeed = 1500.0;
		ProjectileMovementComponent->MaxSpeed = 1500.0;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0;
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
		CollisionComponent->SetSphereRadius(100.f);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
		RootComponent = CollisionComponent;
	}
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->OnSystemFinished.AddDynamic(this, &ThisClass::OnParticleSystemFinished);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::SetTargetGroup(EPawnGroup Group)
{
	switch (Group)
	{
	case EPawnGroup::Enemy:
		CollisionComponent->SetCollisionProfileName(TEXT("EnemyOver"));
		break;
	case EPawnGroup::Friendly:
		CollisionComponent->SetCollisionProfileName(TEXT("FriendlyOver"));
		break;
	default:
		break;
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == TargetActor)  // "Target" 태그를 가진 액터와의 겹침만 처리
	{
		ProjectileMovementComponent->StopMovementImmediately();
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with target actor: %s"), *OtherActor->GetName());
		ParticleSystem->SetTemplate(HitParticleSystem);
		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(TargetActor->GetActorLocation(), GetActorLocation());
		TargetActor->SetActorRotation(LookAtRotator);
		ABasePawn* TargetPawn = Cast<ABasePawn>(TargetActor);
		TargetPawn->HitAnim();
		if (!HitParticleSystem) { Destroy(); }
	}
}

void AProjectile::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//타겟을 향해 날아가며
	//처음 생성할때 바라보는 방향으로 스폰
	//타겟의 위치 , 내 위치 받아서 바라보게 회전하기 근데 가까워서 그냥 바로 갈듯
	//타겟에 닿으면 디스트로이 ㄱ
}

