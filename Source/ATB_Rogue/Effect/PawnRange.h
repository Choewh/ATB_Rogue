// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pool/PooledActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Data/EffectTableRow.h"
#include "Data/StatTableRow.h"
#include "PawnRange.generated.h"
/**
 * 
 */
UCLASS()
class ATB_ROGUE_API APawnRange : public APooledActor
{
	GENERATED_BODY()
	
public:
	APawnRange();

public:
	void SetData(FEffectTableRow& DecalMaterial);


protected:
	virtual void BeginPlay() override;
	
	//UFUNCTION()
	//virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot = nullptr;
	UPROPERTY(VisibleAnywhere)
	UDecalComponent* DecalMeshComponent;

//protected:
//	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/ATB_ROGUE.PawnTableRow"))
//	FDataTableRowHandle DataTableRowHandle;
//
//	FEffectTableRow* EffectData;
};
