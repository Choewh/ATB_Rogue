// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ATBUserWidget.h"
#include "Kismet/GameplayStatics.h"
void UATBUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
	BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	ATBGameInstanceSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UATBGameInstanceSubsystem>();
}

void UATBUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UATBUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//ensure(OwningPawn);
}
