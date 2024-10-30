// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"
#include "Data/SkillTableRow.h"
#include "Data/SpeciesSkillTableRow.h"
#include "Enums/Skills.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATB_ROGUE_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetData(ESpecies InSpecies);
	float GetSkillRange(ESkills InSkill);

public:
	UDataTable* SpeciesSkillDataTable;
	FSpeciesSkillTableRow* SpeciesSkillData;
	FSkillTableRow* FirstSkillData;
	FSkillTableRow* SecondSkillData;
	FSkillTableRow* ThirdSkillData;
};
