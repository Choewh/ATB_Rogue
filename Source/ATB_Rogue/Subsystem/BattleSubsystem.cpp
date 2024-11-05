// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


UBattleSubsystem::UBattleSubsystem()
{
}
void UBattleSubsystem::BattleStart(uint8 Round)
{
	BattleStartFirst.Broadcast(Round);
	BattleStartSecond.Broadcast(Round);
	PawnsActive();

	/// ABTBar 보여주기 Pawn들 소환과 ABTbar 세팅
	/// Pawns 정보 가져오기 배틀중 관리 ㅇㅇ
	///
}
void UBattleSubsystem::BattleEnd()
{
	BattleFinishTurn.Broadcast();

	for (auto& Pawn : EnemyPawns)
	{

	}
	for (auto& Pawn : FriendlyPawns)
	{

	}
}

void UBattleSubsystem::IsDieCheck()
{
	for (int32 i = EnemyPawns.Num() - 1; i >= 0; --i)
	{
		ABasePawn* Pawn = EnemyPawns[i];
		if (EnemyPawns[i]->IsDie())
		{
			EnemyPawns.RemoveAt(i); // 사망한 적을 배열에서 제거
			Pawn->Destroy();
		}
	}
	for (int32 i = FriendlyPawns.Num() - 1; i >= 0; --i)
	{
		ABasePawn* Pawn = FriendlyPawns[i];
		if (FriendlyPawns[i]->IsDie())
		{
			FriendlyPawns.RemoveAt(i); // 사망한 적을 배열에서 제거
			Pawn->Destroy();
		}
	}
}

void UBattleSubsystem::PawnsDeactive()
{
	//인스턴스에서 전부 받아와서 설정
	for (auto& Pawn : EnemyPawns)
	{
		Pawn->SetActive(false);
	}
	for (auto& Pawn : FriendlyPawns)
	{
		Pawn->SetActive(false);
	}
}


void UBattleSubsystem::PawnsActive()
{
	//인스턴스에서 전부 받아와서 설정
	for (auto& Pawn : EnemyPawns)
	{
		Pawn->SetActive(true);
	}
	for (auto& Pawn : FriendlyPawns)
	{
		Pawn->SetActive(true);
	}
}

void UBattleSubsystem::EnterActiveTurn(ABasePawn* InPawn)
{
	PawnsDeactive(); // 그외 에너미 ATB 게이지 회복 중단
	SetActionPawn(InPawn); // 액션폰 설정
	BattleStartTurn.Broadcast();
	InPawn->ActiveCollision(false);
	switch (InPawn->PawnGroup)
	{
	case EPawnGroup::Enemy:
		InPawn->ControllerInit();
		break;
	case EPawnGroup::Friendly:
		SelectActionView();
		break;
	default:
		break;
	}
}

void UBattleSubsystem::SelectActionView()
{
	PlayerController->ShowWidget.Broadcast(); // 제일 첫 Move Attack Wait 메뉴 상태
	SetViewCameraMode(ECameraViewMode::PawnView);
	SetBattleState(EBattleState::Defalut);
	//그럴일없겠지만 있으면 삭제 ㅇㅇ
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
}

void UBattleSubsystem::SelectMoveAction()
{
	SetBattleState(EBattleState::Move);			//이동상태로 변경
	SetViewCameraMode(ECameraViewMode::Move);
	ShowMoveRange();
}
void UBattleSubsystem::ShowMoveRange()
{
	ActionPawn->EffectComponent->ShowRange(ActionPawn->GetActorLocation(), ActionPawn->StatusComponent->GetSpeciesInfo()->MoveRange);
}

void UBattleSubsystem::HideMoveRange()
{
	ActionPawn->EffectComponent->HideRange();
}

//void UEffectComponent::ViewMoveRange(FVector PawnLocation, float MoveRange)
//{
//	float Scale = (MoveRange) / 100;
//	FTransform NewTransform(FRotator::ZeroRotator, PawnLocation, FVector(Scale, Scale, Scale));
//	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->SpawnRangeEffect(NewTransform, *EffectData);
//}
bool UBattleSubsystem::SelectMoveAccept()
{
	if (PlayerController->IsMove())
	{

		FVector NewDestination = PlayerController->GetMovePoint();
		//클릭없었으면 작동 X
		if (NewDestination == FVector::Zero()) { return false; }
		//액션폰에 자기 이동거리 확인 만들기
		AFriendlyPawn* FriendlyPawn = Cast<AFriendlyPawn>(ActionPawn);
		if (!FriendlyPawn->Movealbe(NewDestination))
		{
			return false;
		}
		//이동 가능시 무브
		//폰이 따로 신호주면 턴 종료 ㄱ
		HideMoveRange();
		PlayerController->SetMoveActive(false);
		FriendlyPawn->MoveTo(NewDestination);
		SelectActionView();
		return true;
	}
	return false;
	//실패시 에러 띄움
}

void UBattleSubsystem::SelectMoveCancle()
{
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
	SetBattleState(EBattleState::Defalut);
	SetViewCameraMode(ECameraViewMode::PawnView);
}

void UBattleSubsystem::SelectAttackAction()
{
	SetBattleState(EBattleState::Attack);
	SetViewCameraMode(ECameraViewMode::Attack);
	//사용할 수 있는 스킬 UI에 띄워주기. 사용할 수 있는 스킬 체크하고 사용 못하면 숨김
}

void UBattleSubsystem::SelectAbleFirstSkill()
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	BaseAIController->TargetPawn = nullptr;
	BaseAIController->GetBlackboardComponent()->SetValueAsEnum(TEXT("Skill"), static_cast<uint8>(ESkills::FirstSkill));
}

void UBattleSubsystem::SelectAbleSecondSkill()
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	BaseAIController->TargetPawn = nullptr;
	BaseAIController->GetBlackboardComponent()->SetValueAsEnum(TEXT("Skill"), static_cast<uint8>(ESkills::SecondSkill));
}

void UBattleSubsystem::SelectAbleThirdSkill()
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	BaseAIController->TargetPawn = nullptr;
	BaseAIController->GetBlackboardComponent()->SetValueAsEnum(TEXT("Skill"), static_cast<uint8>(ESkills::ThirdSkill));
}

void UBattleSubsystem::SelectTargetPawn(AActor* TargetPawn)//폰 데이터 전달
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	BaseAIController->TargetPawn = Cast<ABasePawn>(TargetPawn);
	BaseAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPawn"), BaseAIController->TargetPawn);
	BaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bAttack"), true);
	UE_LOG(LogTemp, Log, TEXT("TargetPawn Name : %s"), *TargetPawn->GetName());
	//거리체크하는 태스크
}

void UBattleSubsystem::SelectAttackAccept()
{
	//사용할 스킬 , 타겟 둘 다 있으면 실행 // 선택시 사거리 표시 -> 폰 선택시 해당 폰 공격
	//이거 없애고 그냥 거리체크해서 사거리내에 있으면 바로 사용하기
}

void UBattleSubsystem::SelectAttackCancle()
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	BaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bAttack"), false);
	SetBattleState(EBattleState::Defalut);
	SetViewCameraMode(ECameraViewMode::PawnView);
}

void UBattleSubsystem::Evolution()
{
	ActionPawn->Evolution();
}

void UBattleSubsystem::MoveActionView() //필요없는거같은데 일단 보류
{

}

void UBattleSubsystem::AttackActionView()
{
}


void UBattleSubsystem::FinishTurn()
{
	//액션폰이 에너미였는지 프렌들리 였는지 구분하기
	if (ActionPawn)
	{
		//턴종료시 해야할것
		//액션폰의 ABT 게이지를 비워주고
		//에너미들의 ABTFeeling On 
		//액션폰은 null로 초기화
		ActionPawn->ABTReset();
		ActionPawn->ActiveCollision(true);
		ActionPawn = nullptr;
		//죽은 폰이 있는지 확인하고 배열에서 제거
		IsDieCheck();

		BattleFinishTurn.Broadcast(); //배틀 끝나고 호출할거 싹다 넣어주기
		PawnsActive();
	}
}

void UBattleSubsystem::SetViewCameraMode(ECameraViewMode InViewMode)
{
	PlayerController->SetViewCameraMode(InViewMode);
	PlayerController->CameraViewUpdate();
}

void UBattleSubsystem::SetBattleState(EBattleState InBattleState)
{
	PlayerController->SetBattleState(InBattleState);
	PlayerController->BattleStateUpdate();
}
