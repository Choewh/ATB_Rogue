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
	//TODO
	//Evolution 중이라면 잠깐 멈추고 Evolution 끝나면 하기 
	// Evolution 여러마리라면?
	//Evolution 매니저에 TArray 해놓고 순서대로 진화해주기? ㄱㅊ은듯
	Init();
	BattleStartFirst.Broadcast(Round);
	BattleStartSecond.Broadcast(Round);
	CalcExp();
	//배틀 끝날때마다 초기화 해주니 처음 시작시 한번싹 초기화 해주기
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("FinishTurn"), 4.f, false);
}

void UBattleSubsystem::Init()
{
	Exp = 0;
}

bool UBattleSubsystem::IsDieCheck()
{
	if (EnemyPawns.IsEmpty()) { ensure(false); return false; }
	if (FriendlyPawns.IsEmpty()) { ensure(false); return false; }

	for (int32 i = EnemyPawns.Num() - 1; i >= 0; --i)
	{
		ABasePawn* Pawn = EnemyPawns[i];
		if (EnemyPawns[i] && EnemyPawns[i]->IsDie())
		{
			EnemyPawns[i]->Destroy();
			EnemyPawns.RemoveAt(i); // 사망한 적을 배열에서 제거
		}
	}

	for (int32 i = FriendlyPawns.Num() - 1; i >= 0; --i)
	{
		ABasePawn* Pawn = FriendlyPawns[i];
		if (FriendlyPawns[i] && FriendlyPawns[i]->IsDie())
		{
			FriendlyPawns[i]->Destroy(); //캐릭터쪽으로 정보 전달
			FriendlyPawns.RemoveAt(i); // 사망한 적을 배열에서 제거
		}
	}

	if (FriendlyPawns.IsEmpty())
	{
		//게임오버 -> 메인화면 레벨 오픈
		UGameplayStatics::OpenLevel(this, TEXT("Main"), true);
		return true;
	}

	if (EnemyPawns.IsEmpty())
	{

		BattleEndFirst.Broadcast(Exp); //경험치 계산

		//데이터 저장
		//BattleEndSecond.Broadcast();

		//데이터 저장
		BattleEndThird.Broadcast(); //레벨 전환

		//배틀엔드에 레벨매니저 라운드 or 레벨 데이터 업데이트 후 배틀 시작

		return true;
	}

	return false;
}

bool UBattleSubsystem::AutoPlay()
{
	if (bAuto)
	{
		bAuto = false;
	}
	else
	{
		bAuto = true;
	}

	for (int32 i = 0; i < FriendlyPawns.Num(); i++)
	{
		AFriendlyPawn* Pawn = Cast<AFriendlyPawn>(FriendlyPawns[i]);
		Pawn->OnAutoPlay(bAuto);
	};
	return bAuto;
}

void UBattleSubsystem::EnterActiveTurn(ABasePawn* InPawn)
{
	UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////////EnterActiveTurn")); //Temp

	SetActionPawn(InPawn); // 액션폰 설정
	BattleStartTurn.Broadcast();
	InPawn->ControllerInit();
	InPawn->ActiveCollision(false); // 그냥 병123신같이 움직이는것도 포용하기...
	switch (InPawn->PawnGroup)
	{
	case EPawnGroup::Enemy:
		break;
	case EPawnGroup::Friendly:
		if (bAuto)
		{
			break;
		}
		else
		{
		SelectActionView();
		}
		break;
	default:
		break;
	}
}

void UBattleSubsystem::SelectActionView()
{
	PlayerController->ShowTurnActionWidget.Broadcast(); // 제일 첫 Move Attack Wait 메뉴 상태
	SetViewCameraMode(ECameraViewMode::PawnView);
	SetBattleState(EBattleState::Default);
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
		return true;
	}
	return false;
	//실패시 에러 띄움
}

void UBattleSubsystem::SelectMoveCancle()
{
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
	SetBattleState(EBattleState::Default);
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

void UBattleSubsystem::SelectTargetPawn(AActor* InTargetPawn)//폰 데이터 전달
{
	ABaseAIController* BaseAIController = Cast<ABaseAIController>(ActionPawn->GetController());
	ABasePawn* TargetPawn = Cast<ABasePawn>(InTargetPawn);
	if (TargetPawn)
	{
		BaseAIController->TargetPawn = Cast<ABasePawn>(TargetPawn);
		BaseAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPawn"), BaseAIController->TargetPawn);
		BaseAIController->GetBlackboardComponent()->SetValueAsBool(TEXT("bAttack"), true);
	}
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
	SetBattleState(EBattleState::Default);
	SetViewCameraMode(ECameraViewMode::PawnView);
}

void UBattleSubsystem::Evolution(AActor* EvolutionActor)
{
	ABasePawn* EvolutionPawn = Cast<ABasePawn>(EvolutionActor);
	if (!EvolutionPawn) { ensure(false); return; }
	SetBattleState(EBattleState::Evolution);
	EvolutionPawn->Evolution();
	OnEvolution.Broadcast(EvolutionPawn->Species);
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
		//액션폰의 ATB 게이지를 비워주고
		//에너미들의 ATBFeeling On 
		//액션폰은 null로 초기화
		ActionPawn->ATBReset();
		ActionPawn = nullptr;
		//죽은 폰이 있는지 확인하고 배열에서 제거

		BattleFinishTurn.Broadcast(); //배틀 끝나고 호출할거 싹다 넣어주기

		if (IsDieCheck()) { return; } // bool 반환받고 레벨 전환 또는 라운드 전환 생기면 리턴해주기
	}
	else
	{
		BattleFinishTurn.Broadcast(); //배틀 끝나고 호출할거 싹다 넣어주기
	}
	UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////////FinishTurn")); //Temp
}

void UBattleSubsystem::CalcExp()
{
	for (auto& Pawn : EnemyPawns)
	{
		//레벨
		uint8 a = static_cast<uint8>(Pawn->StatusComponent->GetSpeciesInfo()->Level);
		//단계
		uint8 b = static_cast<uint8>(Pawn->StatusComponent->GetSpeciesInfo()->Stage);
		//보스유무
		uint8 c;
		if (Pawn->StatusComponent->GetSpeciesInfo()->Boss == EBattleSpec::Boss)
		{
			c = 2;
		}
		else
		{
			c = 1.5;
		}
		
		uint32 ResultExp = (a* b* c + 5) * 1000;
	
		Exp += ResultExp;
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
