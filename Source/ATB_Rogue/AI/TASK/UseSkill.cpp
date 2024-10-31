// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TASK/UseSkill.h"
#include "Kismet/GameplayStatics.h"
#include "UseSkill.h"

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
		SkilDamage = DamageCalculation(SkillComponent->FirstSkillData);
		
		//이펙트 재생 -> 이펙트에 닿으면 
		//공격 몽타쥬에 애님노티파이 넣어서 콜리전 껏다 켯다 흠 @TODO
		UGameplayStatics::ApplyDamage(TargetPawn, 10.f, AIOwner, Pawn, nullptr);
		break;

	case ESkills::SecondSkill:
		SkilDamage = DamageCalculation(SkillComponent->SecondSkillData);

		UGameplayStatics::ApplyDamage(TargetPawn, 10.f, AIOwner, Pawn, nullptr);
		// 타수 만큼 반복하는건 따로 생각해보기 ~ 
		break;

	case ESkills::ThirdSkill:
		SkilDamage = DamageCalculation(SkillComponent->ThirdSkillData);

		UGameplayStatics::ApplyDamage(TargetPawn, 10.f, AIOwner, Pawn, nullptr);
		break;
	default:
		break;
	}
	// 이펙트 생성
	// 이펙트 끝나면 피니시 델리게이트 ㄱ? 흠
	// 무브컴플리트와 같이 어택컴플리트 추가하기
}

float UUseSkill::DamageCalculation(FSkillTableRow* UseSkillData)
{
	UseSkillData->Skill_TargetType; // 지금은 간단하게 상대 공격만 ㅇ

	const FSpeciesInfo* Info = StatusComponent->GetSpeciesInfo();

	//데미지 타입마다 추가 뭐가 다른게 있을수도 있으니 ㅇ
	switch (UseSkillData->Skill_DamageType)
	{
	case EHitDamageType::Magic:

		break;

	case EHitDamageType::Melee:

		break;

	default:
		break;
	}
	return 0.f;
}
