// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_HitDamage.h"
#include "Pawn/BasePawn.h"
#include "AI/BaseAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimNotify_HitDamage.h"

UAnimNotify_HitDamage::UAnimNotify_HitDamage()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA
}

void UAnimNotify_HitDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* OwningActor = MeshComp->GetOwner();

#if WITH_EDITOR
	if (GIsEditor && OwningActor && OwningActor->GetWorld() != GWorld) { return; } // ������ ������
#endif
	
	ABasePawn* Pawn = Cast<ABasePawn>(OwningActor);
	ABaseAIController* OwningController = Cast<ABaseAIController>(Pawn->GetController());

	ABasePawn* TargetPawn = OwningController->TargetPawn;
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(TargetPawn->GetActorLocation(), OwningActor->GetActorLocation()); //ȸ���� ��Ƽ���� ��
	TargetPawn->SetActorRotation(LookAtRotator);


	TargetPawn->HitAnim();
}
