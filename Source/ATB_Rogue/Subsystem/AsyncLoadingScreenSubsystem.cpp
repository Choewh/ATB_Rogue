// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/AsyncLoadingScreenSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer.h"
#include "Kismet/GameplayStatics.h"

void UAsyncLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAsyncLoadingScreenSubsystem::OpenLevelWithLoadingScreen(TSubclassOf<UUserWidget> WidgetClass, const TSoftObjectPtr<UWorld> Level)
{
	if (!WidgetClass)
	{
		ensureMsgf(false, TEXT("WidgetClass is nullptr"));
		return;
	}

    LoadingScreenWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
    OpenLevel = Level;
    if (LoadingScreenWidget)
    {
        // 위젯을 뷰포트에 추가하여 표시
        LoadingScreenWidget->AddToViewport();

        // 3초 후에 로딩 화면을 숨기기 위한 타이머 설정
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::NextLevelOpen, 3.f, false);
    }
}

void UAsyncLoadingScreenSubsystem::NextLevelOpen()
{
    //// 로딩 화면 위젯을 숨기기
    //if (LoadingScreenWidget)
    //{
    //    LoadingScreenWidget->RemoveFromViewport();
    //}

    UGameplayStatics::OpenLevelBySoftObjectPtr(this, OpenLevel);
}
