// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"
#include "Data/StatTableRow.h"

#include "Enums/Stat.h"
#include "Enums/Stage.h"
#include "Enums/Species.h"
#include "StatusComponent.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FSpeciesInfo
{
    GENERATED_BODY()
public:
    FSpeciesInfo()
       :Level(0),
        Species(ESpecies::None),
        Stage(EStage::None),
        Attribute(EAttribute::None),
        HP(0.f),
        ATK(0.f),
        DEF(0.f),
        SPATK(0.f),
        SPD(0.f),
        ACC(0.f),
        EVA(0.f),
        MoveRange(1200.f)
    {}

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESpecies Species;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStage Stage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAttribute Attribute;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ATK = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DEF = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SPATK = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SPDEF = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SPD = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ACC = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EVA = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveRange = 1200.f;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATB_ROGUE_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void SetData(ESpecies InSpecies);
public:
	//������ ���̺�
	UDataTable* StatDataTable;
	FStatTableRow* StatData;

public:

	EStage GetStage() { return SpeciesInfo.Get()->Stage; }
	EAttribute GetAttribute() { return SpeciesInfo.Get()->Attribute; }
	float GetStat(EStat StatName);
	float GetMoveRange() { return SpeciesInfo.Get()->MoveRange; }

public:
    TUniquePtr<FSpeciesInfo> GetSpeciesInfo();
	void SetSpeciesInfo(TUniquePtr<FSpeciesInfo> NewSpeciesInfo) { check(!SpeciesInfo); SpeciesInfo = MoveTemp(NewSpeciesInfo); }
protected:
	void ReleaseContext() { check(SpeciesInfo); SpeciesInfo = nullptr; } //지울일이있나?

	TUniquePtr<FSpeciesInfo> SpeciesInfo;
};