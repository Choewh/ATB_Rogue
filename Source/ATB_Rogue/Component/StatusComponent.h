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
 * 베이스 스탯 /
 *
 *
 */
USTRUCT(BlueprintType)
struct FSpeciesInfo
{
	const TArray<uint32> expLevels = { 0, 8, 27, 64, 125, 216, 343, 512, 729, 1000, 1331, 1728, 2197, 2744, 3375, 4096, 4913, 5832, 6859, 8000, 9261, 10648, 12167, 13824, 15625, 17576, 19683, 21952, 24389, 27000, 29791, 32768, 35937, 39304, 42875, 46656, 50653, 54872, 59319, 64000, 68921, 74088, 79507, 85184, 91125, 97336, 103823, 110592, 117649, 125000, 132651, 140608, 148877, 157464, 166375, 175616, 185193, 195112, 205379, 216000, 226981, 238328, 250047, 262144, 274625, 287496, 300763, 314432, 328509, 343000, 357911, 373248, 389017, 405224, 421875, 438976, 456533, 474552, 493039, 512000, 531441, 551368, 571787, 592704, 614125, 636056, 658503, 681472, 704969, 729000, 753571, 778688, 804357, 830584, 857375, 884736, 912673, 941192, 970299, 1000000 };

	GENERATED_BODY()

public:
	FSpeciesInfo(uint8 Level = 1)
		:Level(Level),
		LevelExp(expLevels[Level]),
		Species(ESpecies::None),
		Stage(EStage::None),
		Attribute(EAttribute::None),
		HP(0.f),
		ATK(0.f),
		DEF(0.f),
		SPATK(0.f),
		SPDEF(0.f),
		SPD(0.f),
		ACC(0.f),
		EVA(0.f),
		MoveRange(1200.f)
	{}
	FSpeciesInfo(const FSpeciesInfo& Other)
		: Level(Other.Level),
		LevelExp(Other.LevelExp),
		Species(Other.Species),
		Stage(Other.Stage),
		Attribute(Other.Attribute),
		HP(Other.HP),
		ATK(Other.ATK),
		DEF(Other.DEF),
		SPATK(Other.SPATK),
		SPDEF(Other.SPDEF),
		SPD(Other.SPD),
		ACC(Other.ACC),
		EVA(Other.EVA),
		MoveRange(Other.MoveRange)
	{}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 LevelExp;

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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
public:
	//������ ���̺�
	UDataTable* StatDataTable;
	FStatTableRow* StatData;

public:
	const TSharedPtr<FSpeciesInfo> GetSpeciesInfo() { return SpeciesInfo; }

	void SetSpeciesInfo(TSharedPtr<FSpeciesInfo> NewSpeciesInfo) { SpeciesInfo = NewSpeciesInfo; }
protected:
	void ReleaseContext() { check(SpeciesInfo); SpeciesInfo = nullptr; } //지울일이있나?

private:
	uint8 GetRand() { return FMath::RandRange(85, 100); }
	float AffinityCalcu(EAttribute CauserAttribute, EAttribute thisAttribute);
private:
	TSharedPtr<FSpeciesInfo> SpeciesInfo;

	const float AffinityTable[4][4] = {
		// Vaccine, Data, Virus, Unknown
			{1.0f, 0.5f, 1.5f, 1.0f},   // Vaccine에 대한 상성
			{1.5f, 1.0f, 0.5f, 1.0f},   // Data에 대한 상성
			{0.5f, 1.5f, 1.0f, 1.0f},   // Virus에 대한 상성
			{1.0f, 1.0f, 1.0f, 1.0f}    // Unknown에 대한 상성
	};

};