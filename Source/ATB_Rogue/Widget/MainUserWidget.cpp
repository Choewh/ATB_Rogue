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

}

void UMainUserWidget::NativePreConstruct()
{
}

void UMainUserWidget::NativeConstruct()
{
	CreateButtons(8);
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
			ScrollBoxSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
			ScrollBoxSlot->SynchronizeProperties();
		}
	}
}
UTexture2D* UMainUserWidget::GetTexture2DFromImage(UImage* InImage)
{
	UObject* Texture = InImage->Brush.GetResourceObject();
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
	case 5:
		SelectPawn5->SetBrushFromTexture(Portrait);
		break;
	default:
		break; // CurPawn이 1~5가 아닐 때의 처리
	}
}
bool UMainUserWidget::EnterGame()
{
	if (SelectPawns.IsEmpty()) { return false; }

	UATBGameInstanceSubsystem* GameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UATBGameInstanceSubsystem>();
	bool Result;

	if (GameInstanceSubsystem)
	{
	Result = GameInstanceSubsystem->SavePlayerPawnsInfo(SelectPawns);
	}

	return Result;
}
void UMainUserWidget::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked!"));
}

void UMainUserWidget::SelectPawn(ESpecies SelectSpecies, UImage* Portrait) // 
{
	if (SelectPawns.Num() > 5) { return; }
	SelectPawns.Add(SelectSpecies);
	SelectPawnsUpdata(Portrait);
}

void UMainUserWidget::CreateButtons(uint8 InNum)
{
	ESpecies Species = ESpecies::Jyarimon;
	for (uint8 i = 0; i < InNum; i++)
	{
		//생성할때 Species 에서 종에대한 정보 받고 여기도 폰테이블 추가해서 초상화까지 고려해보기
		//버튼 생성 텍스트 표기
		FText SpeciesText = FUtils::GetSpeciesName(Species);
		FName SpeciesName = *SpeciesText.ToString();

		UOverlay* Overlay = NewObject<UOverlay>(this);


		UImage* Image = NewObject<UImage>(Overlay);
		USelectableCell* SelectableCell = NewObject<USelectableCell>(Overlay);
		Image->SetBrushSize(FVector2D(200.f, 200.f));
		{
			SetSpeciesPortrait.Broadcast(Image, SpeciesName);

		}
		{
			SelectableCell->Species = Species;
			SelectableCell->Image = Image;
			SelectableCell->OnPressed.AddDynamic(this, &ThisClass::OnButtonClicked);
			SelectableCell->AddPawn.AddDynamic(this, &ThisClass::SelectPawn);
		}
		{
			Overlay->AddChild(Image);
			Overlay->AddChild(SelectableCell);
			SelectBox->AddChild(Overlay);
		}

		TArray<UPanelSlot*> Slots = Overlay->GetSlots();
		for (auto& OverlaySlots : Slots)
		{
			UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(OverlaySlots);
			OverlaySlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
			OverlaySlot->VerticalAlignment = EVerticalAlignment::VAlign_Fill;
			OverlaySlot->SynchronizeProperties();
		}

		{
			Species = GetNextSpecies(Species);
			if (Species == ESpecies::None) { break; }
		}
	}
}
