// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatusComponent.h"
#include "Engine/DamageEvents.h"
#include "Pawn/BasePawn.h"
#include "Subsystem/ATBUserUISubSystem.h"
#include "Subsystem/BattleSubSystem.h"
#include "Misc/AllDamageType.h"



// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> StatDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/StatTable.StatTable'"));
	if (StatDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
		StatDataTable = StatDataObject.Object;
	}

	SpeciesInfo = MakeShared<FSpeciesInfo>();
}



// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UStatusComponent::SetData(ESpecies InSpecies)
{
	TArray<FStatTableRow*> StatTable_Array;
	StatDataTable->GetAllRows<FStatTableRow>("", StatTable_Array);

	for (auto& StatTable : StatTable_Array)
	{
		if (StatTable->Species == InSpecies)
		{
			StatData = StatTable;
			break;
		}
	}

	if (!StatData) { UE_LOG(LogTemp, Log, TEXT("StatusComponent is Not Find")); return; }

	{
		TSharedPtr<FSpeciesInfo> NewSpeciesInfo = MakeShared<FSpeciesInfo>();

		//로드 스탯
		NewSpeciesInfo.Get()->Level = SpeciesInfo.Get()->Level;
		NewSpeciesInfo.Get()->LevelExp = SpeciesInfo.Get()->LevelExp;
		NewSpeciesInfo.Get()->Boss = SpeciesInfo.Get()->Boss;

		float Mod1 = 1.f;
		if (NewSpeciesInfo.Get()->Boss == EBattleSpec::Boss)
		{
			Mod1 = 1.2f;
		}
		//베이스 스탯
		NewSpeciesInfo.Get()->Species = InSpecies;
		NewSpeciesInfo.Get()->Stage = StatData->Stage;
		NewSpeciesInfo.Get()->Attribute = StatData->Attribute;

		NewSpeciesInfo.Get()->HP = StatData->HP * Mod1;
		NewSpeciesInfo.Get()->ATK = StatData->ATK * Mod1;
		NewSpeciesInfo.Get()->DEF = StatData->DEF * Mod1;
		NewSpeciesInfo.Get()->SPATK = StatData->SPATK * Mod1;
		NewSpeciesInfo.Get()->SPDEF = StatData->SPDEF * Mod1;

		NewSpeciesInfo.Get()->SPD = StatData->SPD * Mod1;

		//얘네 둘은 아직 안쓰긴함 명중률 회피률
		NewSpeciesInfo.Get()->ACC = StatData->ACC * Mod1;
		NewSpeciesInfo.Get()->EVA = StatData->EVA * Mod1;

		NewSpeciesInfo.Get()->MoveRange = StatData->MoveRange;
		// 베이스 스탯
		// 이후 추가
		SpeciesInfo = NewSpeciesInfo;
	}
}

float UStatusComponent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Damage;

	ABasePawn* DamageCauserPawn = Cast<ABasePawn>(DamageCauser);

	float Mod1 = AffinityCalcu(DamageCauserPawn->StatusComponent->GetSpeciesInfo()->Attribute, SpeciesInfo.Get()->Attribute);

	//보스는 스탯에서 따로 난이도 조절 해주면서 아래는 주석처리
	//float Mod2 = 1.f;

	//if (DamageCauserPawn->StatusComponent->GetSpeciesInfo()->Boss == EBattleSpec::Boss)
	//{
	//	Mod2 = 1.5f;
	//}

	if (DamageEvent.DamageTypeClass == USpecialType::StaticClass())
	{
		NewDamage = (NewDamage / SpeciesInfo.Get()->SPDEF + 2) * GetRand() / 100.f * Mod1;
	}
	else if (DamageEvent.DamageTypeClass == UMeleeType::StaticClass())
	{
		NewDamage = (NewDamage / SpeciesInfo.Get()->DEF + 2) * GetRand() / 100.f * Mod1;
	}
	UE_LOG(LogTemp, Warning, TEXT("ResultDamage : %f"), NewDamage);
	return NewDamage;
}

void UStatusComponent::GetLevelExp(uint16 Exp)
{
	// if(100 < SpeciesInfo.Get()->Level) // 100보다 커지면 적용할것
	uint32 NextLevelExp = SpeciesInfo.Get()->expLevels[SpeciesInfo.Get()->Level];

	SpeciesInfo.Get()->LevelExp += Exp;

	if (SpeciesInfo.Get()->LevelExp >= NextLevelExp)
	{
		SpeciesInfo.Get()->Level++;

		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		//진화레벨일 경우 실행
		switch (SpeciesInfo.Get()->Stage)
		{
		case EStage::Rookie:
			if (SpeciesInfo.Get()->Level >= 16)
				BattleSubsystem->Evolution(GetOwner());
			break;
			//에볼루션 매니저 호출
		case EStage::Champion:
			if (SpeciesInfo.Get()->Level >= 35)
				BattleSubsystem->Evolution(GetOwner());
			break;

		case EStage::Ultimate:
			if (SpeciesInfo.Get()->Level >= 50)
				BattleSubsystem->Evolution(GetOwner());
			break;

		default:
			break;
		}
		//정보 업데이트
		UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
		check(ATBUserUISubSystem);
		ATBUserUISubSystem->UpdatePawnUI(GetOwner());
		//2레벨 업 할수도있으니 GetLevelExp(0)
		GetLevelExp(0);
		//UI 업데이트 짜피 시작할때 할거니까 ㄱㅊ을듯?
	}
}

float UStatusComponent::AffinityCalcu(EAttribute CauserAttribute, EAttribute thisAttribute)
{
	float temp = AffinityTable[static_cast<uint8>(CauserAttribute)][static_cast<uint8>(thisAttribute)];
	return AffinityTable[static_cast<uint8>(CauserAttribute)][static_cast<uint8>(thisAttribute)];
}
