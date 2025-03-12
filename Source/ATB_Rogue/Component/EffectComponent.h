// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Misc/Datas.h"

#include "Effect/PawnGroupEffect.h"

#include "Enums/Species.h"

#include "EffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATB_ROGUE_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void SetData(ESpecies InSpecies);
public:	

public:
	FEffectTableRow* EffectData;
public:
	void ShowRange(FVector PawnLocation,float MoveRange);
	void HideRange();
private:
	APawnGroupEffect* PawnGruopEffect;
};
