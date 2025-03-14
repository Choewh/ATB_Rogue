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
		UClass* WidgetClass = LoadClass<UATBUserWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Battle_Turn.ATB_Battle_Turn_C'"));
		check(WidgetClass);
		TurnActionWidget = CreateWidget<UATBUserWidget>(GetWorld(), WidgetClass);
	}
	{
		UClass* WidgetClass = LoadClass<UATBUserWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Battle_Menu.ATB_Battle_Menu_C'"));
		check(WidgetClass);
		BattleMenuUI = CreateWidget<UATBUserWidget>(GetWorld(), WidgetClass);
	}
	{
		UClass* WidgetClass = LoadClass<UATBUserWidget>(nullptr,
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/Battle/ATB_Battle_Utils.ATB_Battle_Utils_C'"));
		check(WidgetClass);
		BattleUtilsUI = CreateWidget<UATBUserWidget>(GetWorld(), WidgetClass);
	}
	//배틀시스템에서 하기 오너는 폰으로 셋 해주기
	/*UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	check(BattleSubsystem);
	BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowATBBar);

	PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PlayerController);
	PlayerController->ShowTurnActionWidget.AddDynamic(this, &AATBHUD::ShowTurnActionWidget);*/
}
void AATBHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//배틀시스템에서 하기 오너는 폰으로 셋 해주기
	{
		UATBUserUISubSystem* ATBUserUISubSystem = GetWorld()->GetSubsystem<UATBUserUISubSystem>();
		check(ATBUserUISubSystem);
		ATBUserUISubSystem->AddPawnUI.AddDynamic(this, &ThisClass::AddPawnBattleUI);
		ATBUserUISubSystem->RemovePawnUI.AddDynamic(this, &ThisClass::RemovePawnBattleUI);
		ATBUserUISubSystem->UpdatePawnUIUI.AddDynamic(this, &ThisClass::UpdatePawnUI);
		ATBUserUISubSystem->ShowBattleMenu.AddDynamic(this, &ThisClass::ShowBattleMenuUI);
		int a = 0;

	}
	{
		UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
		check(BattleSubsystem);
		BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowBattleUI);
		BattleSubsystem->BattleStartSecond.AddDynamic(this, &ThisClass::ShowBattleUtilsUI);

		BattleSubsystem->BattleEndSecond.AddDynamic(this, &ThisClass::HideBattleUI);
		BattleSubsystem->BattleEndSecond.AddDynamic(this, &ThisClass::HideBattleUtilsUI);
	}

	{
		PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		check(PlayerController);
		PlayerController->ShowTurnActionWidget.AddDynamic(this, &AATBHUD::ShowTurnActionWidget);
	}
}
void AATBHUD::BeginPlay()
{
	Super::BeginPlay();
}



void AATBHUD::AddPawnBattleUI(ABasePawn* InPawn)
{
	ATBBattleUserWidget->AddPawnUI(InPawn);
}

void AATBHUD::RemovePawnBattleUI(ABasePawn* DeadPawn)
{
	ATBBattleUserWidget->RemovePawnUI(DeadPawn);
}

void AATBHUD::UpdatePawnUI(ABasePawn* UpdatePawn)
{
	ATBBattleUserWidget->OnUpdateUI(UpdatePawn);
}

void AATBHUD::ShowBattleUI(uint8 Round)
{
	if (ATBBattleUserWidget && !ATBBattleUserWidget->IsInViewport())
	{
		ATBBattleUserWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 뷰포트에 추가되었습니다."));
	}

	// 가시성 조정 (보이도록 설정)
	ATBBattleUserWidget->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
}

void AATBHUD::HideBattleUI()
{
	if (ATBBattleUserWidget && ATBBattleUserWidget->IsInViewport())
	{
		ATBBattleUserWidget->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
	//if (ATBWidget && !ATBWidget->IsInViewport())
	//{
	//	ATBWidget->SetPortrait.Broadcast();
	//	ATBWidget->AddToViewport();
	//	UE_LOG(LogTemp, Log, TEXT("ShowATBBarAddTOViewport 바인딩 성공"));
	//}
}
void AATBHUD::ShowBattleUtilsUI(uint8 Round)
{
	if (BattleUtilsUI && !BattleUtilsUI->IsInViewport())
	{
		BattleUtilsUI->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 뷰포트에 추가되었습니다."));
	}

	// 가시성 조정 (보이도록 설정)
	BattleUtilsUI->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
}
void AATBHUD::HideBattleUtilsUI()
{
	if (BattleUtilsUI && BattleUtilsUI->IsInViewport())
	{
		BattleUtilsUI->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
}
void AATBHUD::ShowTurnActionWidget()
{
	if (TurnActionWidget && !TurnActionWidget->IsInViewport())
	{
		TurnActionWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}

	TurnActionWidget->SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
}
void AATBHUD::HideTurnActionWidget()
{
	if (TurnActionWidget && TurnActionWidget->IsInViewport())
	{
		TurnActionWidget->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
	}
}
void AATBHUD::ShowBattleMenuUI()
{
	if (BattleMenuUI && !BattleMenuUI->IsInViewport())
	{
		BattleMenuUI->AddToViewport();
		BattleMenuUI->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Log, TEXT("UI가 뷰포트에 추가되었습니다."));
		return;
	}

	// 가시성 조정 (보이도록 설정)
	switch (BattleMenuUI->GetVisibility())
	{
	case ESlateVisibility::Visible:
		BattleMenuUI->SetVisibility(ESlateVisibility::Hidden);

		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));

		break;
	case ESlateVisibility::Hidden:
		BattleMenuUI->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Log, TEXT("UI가 보입니다."));
		break;
	default:
		break;
	}
}



//AddTOViewport 를 PlayerController에 델리게이트 만들어서 온오프 기능 바인드
