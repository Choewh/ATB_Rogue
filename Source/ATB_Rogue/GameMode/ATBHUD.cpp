// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ATBHUD.h"
#include "GameMode/ATBUserWidget.h"
#include "GameMode/BasePlayerController.h"
#include "Subsystem/ATBUserUISubSystem.h"
#include "Kismet/GameplayStatics.h"

AATBHUD::AATBHUD()
{
	{
		UClass* WidgetClass = LoadClass<UATBBattleUserWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Battle_UI.ATB_Battle_UI_C'"));
		check(WidgetClass);
		ATBBattleUserWidget = CreateWidget<UATBBattleUserWidget>(GetWorld(), WidgetClass);
	}
	{
		//UClass* WidgetClass = LoadClass<UATBBarUserWidget>(nullptr,
		//TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar_C'"));///Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar'
		//check(WidgetClass);
		//ATBWidget = CreateWidget<UATBBarUserWidget>(GetWorld(), WidgetClass);

	}
	//배틀시스템에서 하기 오너는 폰으로 셋 해주기
	/*UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowATBBar);

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PlayerController);
	PlayerController->ShowWidget.AddDynamic(this, &AATBHUD::ShowViewPort);*/
}
void AATBHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//배틀시스템에서 하기 오너는 폰으로 셋 해주기
	UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
	check(ATBUserUISubSystem);
	ATBUserUISubSystem->AddPawnUI.AddDynamic(this, &ThisClass::AddPawnBattleUI);
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowBattleUI);

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PlayerController);
	PlayerController->ShowWidget.AddDynamic(this, &AATBHUD::ShowViewPort);
}
void AATBHUD::BeginPlay()
{
	Super::BeginPlay();
}



void AATBHUD::AddPawnBattleUI(ABasePawn* InPawn)
{
	ATBBattleUserWidget->AddPawnUI(InPawn);
}

void AATBHUD::ShowBattleUI(uint8 Round)
{
	if (ATBBattleUserWidget && !ATBBattleUserWidget->IsInViewport())
	{
		ATBBattleUserWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
	//if (ATBWidget && !ATBWidget->IsInViewport())
	//{
	//	ATBWidget->SetPortrait.Broadcast();
	//	ATBWidget->AddToViewport();
	//	UE_LOG(LogTemp, Log, TEXT("ShowATBBarAddTOViewport 바인딩 성공"));
	//}
}

void AATBHUD::ShowViewPort()
{
	//if (Widget && !Widget->IsInViewport())
	//{
	//	Widget->AddToViewport();
	//	UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	//}
}



//AddTOViewport 를 PlayerController에 델리게이트 만들어서 온오프 기능 바인드
