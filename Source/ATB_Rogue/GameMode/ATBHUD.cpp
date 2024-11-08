// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ATBHUD.h"
#include "GameMode/ATBUserWidget.h"
#include "GameMode/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

AATBHUD::AATBHUD()
{
	{
		//UClass* WidgetClass = LoadClass<UATBBarUserWidget>(nullptr,
		//TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar_C'"));///Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar'
		//check(WidgetClass);
		//ATBWidget = CreateWidget<UATBBarUserWidget>(GetWorld(), WidgetClass);

	}
	{
		//UClass* WidgetClass = LoadClass<UATBUserWidget>(nullptr,
		//	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_User_UI.ATB_User_UI_C'"));
		//check(WidgetClass);
		//Widget = CreateWidget<UATBUserWidget>(GetWorld(), WidgetClass);
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
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowATBBar);

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PlayerController);
	PlayerController->ShowWidget.AddDynamic(this, &AATBHUD::ShowViewPort);
}
void AATBHUD::BeginPlay()
{
	//Super::BeginPlay();
	//{
	//	UClass* WidgetClass = LoadClass<UATBBarUserWidget>(nullptr,
	//		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar_C'"));///Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Bar.ATB_Bar'
	//	check(WidgetClass);
	//	ATBWidget = CreateWidget<UATBBarUserWidget>(GetWorld(), WidgetClass);

	//}
	//{
	//	UClass* WidgetClass = LoadClass<UATBUserWidget>(nullptr,
	//		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_User_UI.ATB_User_UI_C'"));
	//	check(WidgetClass);
	//	Widget = CreateWidget<UATBUserWidget>(GetWorld(), WidgetClass);
	//}
	//{  //Temp
	//	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr,
	//		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Test.Test_C'"));
	//	check(WidgetClass);
	//	UUserWidget* Test = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	//	Test->AddToViewport();
	//}
	////배틀시스템에서 하기 오너는 폰으로 셋 해주기
	//UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	//check(BattleSubsystem);
	//BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowATBBar);

	//PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	//check(PlayerController);
	//PlayerController->ShowWidget.AddDynamic(this, &AATBHUD::ShowViewPort);
}



void AATBHUD::ShowATBBar(uint8 Round)
{

	if (ATBWidget && !ATBWidget->IsInViewport())
	{
		ATBWidget->SetPortrait.Broadcast();
		ATBWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("ShowATBBarAddTOViewport 바인딩 성공"));
	}
}

void AATBHUD::ShowViewPort()
{
	if (Widget && !Widget->IsInViewport())
	{
		Widget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
}



//AddTOViewport 를 PlayerController에 델리게이트 만들어서 온오프 기능 바인드
