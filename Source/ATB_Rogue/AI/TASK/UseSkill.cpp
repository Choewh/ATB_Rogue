// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/UseSkill.h"
#include "Kismet/GameplayStatics.h"
#include "UseSkill.h"
#include "Subsystem/BattleSubsystem.h"
#include "Damage/Type/MeleeType.h"
#include "Damage/Type/SpecialType.h"

UUseSkill::UUseSkill()
{

	NodeName = "UseSkill";

}

EBTNodeResult::Type UUseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	{
		BehaviorTreeComponent = &OwnerComp;
		SetOwner(BehaviorTreeComponent->GetOwner());
		BlackboardComponent = OwnerComp.GetBlackboardComponent();
	}
	GetWorld()->GetSubsystem<UBattleSubsystem>()->RemoveWidget.Broadcast();
	UseSkillSet(UseSkillSelect);
	

	return EBTNodeResult::Succeeded;
}

void UUseSkill::UseSkillSet(ESkills SkillNum)
{
	ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
	SkillComponent = Pawn->SkillComponent;
	StatusComponent = Pawn->StatusComponent;
	AActor* TargetPawn = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")));
	float SkilDamage;
	Pawn->PlaySkillAnimation(SkillNum); // 애니메이션 재생
	switch (SkillNum)
	{
	case ESkills::FirstSkill:
		Pawn->EffectComponent->HideRange();
		SkilDamage = DamageCalculation(SkillComponent->FirstSkillData);
		break;

	case ESkills::SecondSkill:
		Pawn->EffectComponent->HideRange();
		SkilDamage = DamageCalculation(SkillComponent->SecondSkillData);

		
		// 타수 만큼 반복하는건 따로 생각해보기 ~ 
		break;

	case ESkills::ThirdSkill:
		Pawn->EffectComponent->HideRange();
		SkilDamage = DamageCalculation(SkillComponent->ThirdSkillData);

		break;
	default:
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("SkillDamage : %f"),SkilDamage);
	// 이펙트 생성
	// 이펙트 끝나면 피니시 델리게이트 ㄱ? 흠
	// 무브컴플리트와 같이 어택컴플리트 추가하기
}

float UUseSkill::DamageCalculation(FSkillTableRow* UseSkillData)
{
	//UseSkillData->Skill_TargetType; // 지금은 간단하게 상대 공격만 ㅇ
	ABasePawn* Pawn = Cast<ABasePawn>(AIOwner->GetPawn());
	AActor* TargetPawn = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("TargetPawn")));
	const FSpeciesInfo* Info = StatusComponent->GetSpeciesInfo().Get();
	float ResultDamage = 0.f;

	//데미지 타입마다 추가 뭐가 다른게 있을수도 있으니 ㅇ
	switch (UseSkillData->Skill_DamageType)
	{
	case EHitDamageType::Special:

		ResultDamage = (((Info->Level * 2 / 5) + 2) * UseSkillData->Skill_Damage * Info->SPATK / 50);
		ResultDamage = (Info->SPATK * static_cast<uint8>(Info->Stage) * (Info->Level / 10.f) + 5) * (UseSkillData->Skill_Damage / 10);

		UGameplayStatics::ApplyDamage(TargetPawn, ResultDamage, AIOwner, Pawn, USpecialType::StaticClass());

		break;

	case EHitDamageType::Melee:
		
		// ((레벨 × 2 ÷ 5) + 2) × 위력 × 특수공격 ÷ 50) ~  ÷ 특수방어)×  랜덤수 ÷ 100)
		//((((((레벨 × 2 ÷ 5) + 2) × 위력 × 특수공격 ÷ 50) ÷ 특수방어) + 2) × 랜덤수 ÷ 100)

		ResultDamage = (((Info->Level * 2 / 5) + 2) * UseSkillData->Skill_Damage * Info->ATK / 50);
		//ResultDamage = (Info->ATK * static_cast<uint8>(Info->Stage) * (Info->Level / 10.f) + 5) * (UseSkillData->Skill_Damage / 10);

		UGameplayStatics::ApplyDamage(TargetPawn, ResultDamage, AIOwner, Pawn, UMeleeType::StaticClass());

		break;

	default:
		break;
	}
	return ResultDamage;
}
