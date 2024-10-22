// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/ActorpoolSubsystem.h"
#include "Kismet/GameplayStatics.h"

UBattleSubsystem::UBattleSubsystem()
{
}
void UBattleSubsystem::BattleStart()
{
	Pawns = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UATBGameInstanceSubsystem>()->GetPawns();
	//SetPortraits();
	for (auto& Pawn : Pawns)
	{
		//폰만 받아오고 위치 알아서 ㄱ
		UGameplayStatics::GetGameInstance(this)->GetSubsystem<UATBGameInstanceSubsystem>()->ActivatePawn(Pawn);
	}
	StartBattle.Broadcast();
}
void UBattleSubsystem::BattleEnd()
{
	for (auto& Pawn : Pawns)
	{
		UGameplayStatics::GetGameInstance(this)->GetSubsystem<UATBGameInstanceSubsystem>()->DeactivatePawn(Pawn);
	}
}
//여기서 ATB 게이지에 초상화도 세팅
void UBattleSubsystem::SetPortraits()
{
	for (auto& Pawn : Pawns)
	{
		//SetPortrait.Broadcast(Pawn->PawnData->Portraits);
		FString LogMessage = Pawn->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
	}
	//HUD 델리게이트?
}

void UBattleSubsystem::PawnAction()
{
	if (ActionPawn->PawnGroup == EPawnGroup::Friendly)
	{	//플레이어 폰일때 할 행동들
		if (PlayerController) { PlayerController->Init(); }

		if (!PlayerController->SetViewCameraMode(ECameraViewMode::PawnView))
		{
			return;//전환실패시 종료 턴종료 에러임 ㅇㅇ
		}
		SelectActionView();
	}
	// Ex.Move // Player Controller/Camera Move ->  
	// PlayerController/TargetPosition -> BattleSystem/Move To 
	// -> Pawn이동 -> 현재는 턴 종료 로 마무리 하기 
}

void UBattleSubsystem::PawnsDeactive()
{
	//인스턴스에서 전부 받아와서 설정
	for(ABasePawn* Pawn : Pawns)
	{
		Pawn->SetActive(false);
	}
}

	
void UBattleSubsystem::PawnsActive()
{
	//인스턴스에서 전부 받아와서 설정
	for (ABasePawn* Pawn : Pawns)
	{
		Pawn->SetActive(true);
	}
}

void UBattleSubsystem::EnterActiveTurn(ABasePawn* InPawn)
{
	PawnsDeactive(); // 그외 에너미 ATB 게이지 회복 중단
	SetActionPawn(InPawn); // 액션폰 설정
	PawnAction();
}

void UBattleSubsystem::SelectActionView()
{
	PlayerController->ShowWidget.Broadcast(); // 제일 첫 Move Attack Wait 메뉴 상태
	PlayerController->PawnAroundView(ActionPawn);
	//그럴일없겠지만 있으면 삭제 ㅇㅇ
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
	//폰에서 사거리 그려주기 어떻게?
}

void UBattleSubsystem::SelectMoveAction()
{
	PlayerController->SetBattleState(EBattleState::Move);				//이동상태로 변경
	PlayerController->SetViewCameraMode(ECameraViewMode::DefaultView);	//카메라 뷰 디폴트로 변경
	ActionPawn->MakeViewMoveRange();
}
bool UBattleSubsystem::SelectMoveAccept()
{
	FVector NewDestination = PlayerController->GetMovePoint();
	//클릭없었으면 작동 X
	if (NewDestination == FVector::Zero()) { return false; }
	//액션폰에 자기 이동거리 확인 만들기
	if (!ActionPawn->Movealbe(NewDestination))
	{
		return false;
	}
	//이동 가능시 무브
	if (ActionPawn->MoveTo(NewDestination))
	{
		FinishTrun();
		PlayerController->SetBattleState(EBattleState::Move);
		GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
		return true;
	}
	return false;
	//실패시 에러 띄움
}

void UBattleSubsystem::SelectMoveCancle()
{
	GetWorld()->GetSubsystem<UActorpoolSubsystem>()->DeSpawnRangeEffect();
	PlayerController->SetBattleState(EBattleState::Defalut);
	PlayerController->SetViewCameraMode(ECameraViewMode::PawnView);
	PlayerController->PawnAroundView(ActionPawn);
}

void UBattleSubsystem::MoveActionView() //필요없는거같은데 일단 보류
{

}

void UBattleSubsystem::AttackActionView()
{
}


void UBattleSubsystem::FinishTrun()
{
	if (ActionPawn)
	{
		//턴종료시 해야할것
		//액션폰의 ABT 게이지를 비워주고
		//에너미들의 ABTFeeling On 
		//액션폰은 null로 초기화
		ActionPawn->ABTReset(); 
		PawnsActive();
		ActionPawn = nullptr;
		FBattleEnd.Broadcast();
	}
}
