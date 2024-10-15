// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/BattleSubsystem.h"

UBattleSubsystem::UBattleSubsystem()
{
}

void UBattleSubsystem::EntryEnemy(ABasePawn* EntryEnemy)
{
	ABasePawn* Pawn = Cast<ABasePawn>(EntryEnemy);
	Playerble.Add(Pawn);
	
	FString LogMessage = EntryEnemy->GetName();
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogMessage);
}

void UBattleSubsystem::EnemyDeactive()
{
	for(ABasePawn* enemy : Playerble)
	{
		enemy->SetActive(false);
	}
}

void UBattleSubsystem::ActiveTurn(ABasePawn* Enemy)
{
	EnemyDeactive(); // 그외 에너미 ATB 게이지 회복 중단
	PlayerController->Cameraarrangement(Enemy); // 턴 진행하는 에너미에 카메라 이동
	//UI 를 띄워줌 이동 공격 대기
	// 버튼에 따라 필요한 함수 실행
	// 
	// 
	// Ex.Move // Player Controller/Camera Move ->  PlayerController/TargetPosition -> BattleSystem/Move To -> Pawn이동 -> 현재는 턴 종료 로 마무리 하기 
}

void UBattleSubsystem::MoveTo(ABasePawn* Enemy, FVector TargetLocation)
{

}
