// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/BattleSubsystem.h"

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
	EnemyDeactive();
	// Camera Move -> 폰에서 행동 처리 -> Move To -> ~~ 생략 -> 
}

void UBattleSubsystem::MoveTo(ABasePawn* Enemy, FVector TargetLocation)
{

}
