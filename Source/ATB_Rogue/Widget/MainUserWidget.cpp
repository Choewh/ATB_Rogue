// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainUserWidget.h"

#include "Misc/Utils.h"

#include "Data/PawnTableRow.h"

#include "Widget/USelectableCell.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/OverlaySlot.h"
#include "Components/ButtonSlot.h"
#include "Subsystem/EnemyCreateSubsystem.h"
#include "Subsystem/ATBGameInstanceSubsystem.h"

#include "Engine/DataTable.h"
#include "Data/StatTableRow.h"
#include "Data/PawnTableRow.h"

#include "Enums/Species.h"

#include "MainUserWidget.h"


ESpecies GetNextSpecies(ESpecies CurrentSpecies)
{
	// CurrentSpecies 값을 정수형으로 변환
	int32 CurrentValue = static_cast<int32>(CurrentSpecies);

	// 다음 값을 계산
	int32 NextValue = CurrentValue + 1;

	// Max 값을 초과하지 않도록 체크
	if (NextValue < static_cast<int32>(ESpecies::End))
	{
		return static_cast<ESpecies>(NextValue);
	}
	return ESpecies::None; // Max를 넘으면 None으로 리셋
}

void UMainUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//폰데이터 테이블과 //초상화 
	//스탯 데이터 테이블 // 단계 Rookie 단계의 Pawn Species Name 뽑아서 배열에 추가
	UDataTable* StatDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/DataTable/StatTable.StatTable")));
	if (StatDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("StatData Succeeded"));
		//StatDataTable

		TArray<FStatTableRow*> StatTable_Array;
		StatDataTable->GetAllRows<FStatTableRow>("", StatTable_Array);

		for (auto& StatTable : StatTable_Array)
		{
			if (StatTable->Stage == EStage::Rookie)
			{
				FText SpeciesText = FUtils::GetSpeciesName(StatTable->Species);
				FName SpeciesName = *SpeciesText.ToString();
				SelectAblePawnNames.Add(SpeciesName);
				continue;
			}
		}
	}
}

void UMainUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMainUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CreateButtons(0);
	Init();
	//델리게이트 만들어서 생성해서 블루프린트에서 해결하는걸로 변경하기
}
void UMainUserWidget::Init()
{
	//폰테이블	
	{   // Scroll SizeRule Fill set
		TArray<UPanelSlot*> BoxSlots = SelectBox->GetSlots();
		for (auto& BoxSlot : BoxSlots)
		{
			UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(BoxSlot);
			ScrollBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
			ScrollBoxSlot->SynchronizeProperties();
		}
	}
}
UTexture2D* UMainUserWidget::GetTexture2DFromImage(UImage* InImage)
{
	UObject* Texture = InImage->GetBrush().GetResourceObject();
	return Cast<UTexture2D>(Texture);
}
void UMainUserWidget::SelectPawnsUpdata(UImage* PortraitImage)
{
	int32 CurPawn = SelectPawns.Num();
	UTexture2D* Portrait = GetTexture2DFromImage(PortraitImage);
	switch (CurPawn)
	{
	case 1:
		SelectPawn1->SetBrushFromTexture(Portrait);
		break;
	case 2:
		SelectPawn2->SetBrushFromTexture(Portrait);
		break;
	case 3:
		SelectPawn3->SetBrushFromTexture(Portrait);
		break;
	case 4:
		SelectPawn4->SetBrushFromTexture(Portrait);
		break;
	case 5:
		SelectPawn5->SetBrushFromTexture(Portrait);
		break;
	default:
		break; // CurPawn이 1~5가 아닐 때의 처리
	}
}
void UMainUserWidget::AddedPawnsDelete()
{
	if (SelectPawns.IsEmpty()) { return; }
	int32 CurPawn = SelectPawns.Num();
	switch (CurPawn)
	{
	case 1:
		SelectPawn1->SetBrushFromTexture(nullptr);
		break;
	case 2:
		SelectPawn2->SetBrushFromTexture(nullptr);
		break;
	case 3:
		SelectPawn3->SetBrushFromTexture(nullptr);
		break;
	case 4:
		SelectPawn4->SetBrushFromTexture(nullptr);
		break;
	case 5:
		SelectPawn5->SetBrushFromTexture(nullptr);
		break;
	default:
		break; // CurPawn이 1~5가 아닐 때의 처리
	}
	SelectPawns.Pop();
}
bool UMainUserWidget::EnterGame()
{
	if (SelectPawns.IsEmpty()) { return false; }

	UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
	bool Result = false;

	if (GameInstanceSubsystem)
	{
		Result = GameInstanceSubsystem->InitSpawnPlayerPawnSpecies(SelectPawns);
	}

	return Result;
}

void UMainUserWidget::SelectPawn(ESpecies SelectSpecies, UImage* Portrait) // 
{
	if (SelectPawns.Num() > 5) { return; }
	SelectPawns.Add(SelectSpecies);
	SelectPawnsUpdata(Portrait);
}

void UMainUserWidget::CreateButtons(uint8 InNum)
{
	for (uint8 i = 0; i < SelectAblePawnNames.Num(); i++)
	{
		//생성할때 Species 에서 종에대한 정보 받고 여기도 폰테이블 추가해서 초상화까지 고려해보기
		//버튼 생성 텍스트 표기
		UOverlay* Overlay = NewObject<UOverlay>(this);
		UImage* Image = NewObject<UImage>(Overlay);
		USelectableCell* SelectableCell = NewObject<USelectableCell>(Overlay);

		SelectBox->AddChild(Overlay);
		Overlay->AddChild(Image);
		Overlay->AddChild(SelectableCell);

		Image->SetDesiredSizeOverride(FVector2D(200.f, 200.f));

		{

			UEnum* EnumPtr = StaticEnum<ESpecies>();
			if (EnumPtr)
			{
				// 2. FName을 Enum 값으로 변환하기
				FName StageName = SelectAblePawnNames[i]; // 예를 들어 "Rookie"라는 이름이 열거형에 있다고 가정
				int32 EnumIndex = EnumPtr->GetIndexByName(StageName);
				SelectableCell->Species = static_cast<ESpecies>(EnumIndex);

				UDataTable* PawnDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/PawnTableRow.PawnTableRow'")));
					if (PawnDataTable)
					{
						UE_LOG(LogTemp, Warning, TEXT("PawnData Succeeded"));

						TArray<FPawnTableRow*> PawnTable_Array;
						PawnDataTable->GetAllRows<FPawnTableRow>("", PawnTable_Array);

						for (auto& PawnTable : PawnTable_Array)
						{
							if (PawnTable->Species == SelectableCell->Species)
							{
								Image->SetBrushFromTexture(PawnTable->Portraits);
								continue;
							}
						}
					}
				SelectableCell->Image = Image;
				SelectableCell->AddPawn.AddDynamic(this, &ThisClass::SelectPawn);
			}
		}

		TArray<UPanelSlot*> Slots = Overlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);

			OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			OverlaySlot->SynchronizeProperties();
		}
	}
}
