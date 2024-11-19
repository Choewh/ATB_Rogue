// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_ProjectileEffect.h"
#include "Pawn/BasePawn.h"
#include "AI/BaseAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Projectile.h"
#include "AnimNotify_ProjectileEffect.h"

UAnimNotify_ProjectileEffect::UAnimNotify_ProjectileEffect()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(0, 0, 255, 255);
#endif // WITH_EDITORONLY_DATA
}

void UAnimNotify_ProjectileEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!ParticleSystem) { return; } //파티클 없으면 패스

	AActor* OwningActor = MeshComp->GetOwner();

#if WITH_EDITOR
	if (GIsEditor && OwningActor && OwningActor->GetWorld() != GWorld) { return; } // ������ ������
#endif

	ABasePawn* Pawn = Cast<ABasePawn>(OwningActor);
	ABaseAIController* OwningController = Cast<ABaseAIController>(Pawn->GetController());

	ABasePawn* TargetPawn = OwningController->TargetPawn;

	const FVector SpawnSocketLocation = MeshComp->GetSocketLocation(SocketName);

	//클래스는 기본 베이스
	UWorld* World = OwningActor->GetWorld();
	//SpawnActorDeferred 아직 생성안댐 -> 61번줄
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(),
		FTransform::Identity, Pawn, Pawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//셋데이터에서 Edit에서 설정해준 파티클로 설정해주기
	Projectile->SetTargetActor(TargetPawn);
	Projectile->SetParticleSystem(ParticleSystem);
	Projectile->SetHitParticleSystem(HitParticleSystem);
	Projectile->SetTargetGroup(TargetPawn->PawnGroup);
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation( OwningActor->GetActorLocation(),TargetPawn->GetActorLocation()); //ȸ���� ��Ƽ���� ��
	Projectile->SetActorRotation(LookAtRotator);
	FTransform NewTransform;
	NewTransform.SetLocation(SpawnSocketLocation);
	Projectile->SetLifeSpan(2.f);
	//여기서 피니시 스포닝으로 생성
	Projectile->FinishSpawning(NewTransform);
}
