// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ABTUserWidget.h"
#include "Kismet/GameplayStatics.h"
void UABTUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
	BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	ATBGameInstanceSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UATBGameInstanceSubsystem>();
}

void UABTUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UABTUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ensure(OwningPawn);
}
