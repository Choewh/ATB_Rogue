// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	//Pawn
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> PawnDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/PawnTableRow.PawnTableRow'"));
		if (PawnDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			PawnDataTable = PawnDataObject.Object;
		}
	}
	//Stat
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> StatDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/StatTable.StatTable'"));
		if (StatDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			StatDataTable = StatDataObject.Object;
		}
	}
	//Skill
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/SpeciesSkillTable.SpeciesSkillTable'"));
		if (SkillDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillData Succeeded"));
			SkillDataTable = SkillDataObject.Object;
		}
	}
	//Effect
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> EffectDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/EffectTableRow.EffectTableRow'"));
		if (EffectDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("EffectData Succeeded"));
			EffectDataTable = EffectDataObject.Object;
		}
	}
	//Animation
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> AnimDataObject(TEXT("/Script/Engine.DataTable'/Game/DataTable/AnimTableRow.AnimTableRow'"));
		if (AnimDataObject.Succeeded())
		{
			UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));
			AnimDataTable = AnimDataObject.Object;
		}
	}
}

