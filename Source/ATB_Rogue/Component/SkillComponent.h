// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Misc/Datas.h"
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

public:
	virtual void SetData(ESpecies InSpecies);

	FSkillTableRow* GetSkillData(ESkills InSkill);
public:
	FSpeciesSkillTableRow* SkillData;
	FSkillTableRow* FirstSkillData;
	FSkillTableRow* SecondSkillData;
	FSkillTableRow* ThirdSkillData;
};
