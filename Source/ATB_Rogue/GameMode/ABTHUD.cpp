// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ABTHUD.h"
#include "GameMode/ABTUserWidget.h"
#include "GameMode/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

AABTHUD::AABTHUD()
{
}

void AABTHUD::BeginPlay()
{
	Super::BeginPlay();

	{
	UClass* WidgetClass = LoadClass<UABTUserWidget>(nullptr,
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/ABT_User_UI.ABT_User_UI_C'"));
	check(WidgetClass);
	Widget = CreateWidget<UABTUserWidget>(GetWorld(), WidgetClass);
	}
	{
		UClass* WidgetClass = LoadClass<UUserWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/ABT_Bar.ABT_Bar_C'"));
		check(WidgetClass);
		ATBWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		ATBWidget->AddToViewport();
	}
	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this,0));
	check(PlayerController);
	PlayerController->ShowWidget.AddDynamic(this, &AABTHUD::ShowViewPort);
	UE_LOG(LogTemp, Log, TEXT("ShowViewPort 바인딩 성공"));
}

void AABTHUD::ShowViewPort()
{
	if (Widget && !Widget->IsInViewport()) 
	{
		Widget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
}



//AddTOViewport 를 PlayerController에 델리게이트 만들어서 온오프 기능 바인드
