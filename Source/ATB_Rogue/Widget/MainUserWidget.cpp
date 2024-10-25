// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainUserWidget.h"

#include "Misc/Utils.h"

#include "Data/PawnTableRow.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/ButtonSlot.h"

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
		FSlateChildSize SlateChildSize(ESlateSizeRule::Fill);
		for (auto& BoxSlot : BoxSlots)
		{
			UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(BoxSlot);
			ScrollBoxSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
			ScrollBoxSlot->SynchronizeProperties();
		}
	}
}
void UMainUserWidget::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked!"));
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
		UButton* Button = NewObject<UButton>(this);
		UImage* Image = NewObject<UImage>(Button);
		Image->SetBrushSize(FVector2D(200.f, 200.f));

		{	//폰데이터 찾기
			SetSpeciesPortrait.Broadcast(Image, SpeciesName);
			//이미지 추가해서 바꿔주기
		}
		// 클릭 -> 버튼 버튼이 폰을 어떻게 전달하나
		// 위젯에 델리게이트 생성 버튼의 함수 ?
		{
			Button->AddChild(Image);
			Button->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked); // 클릭시 데이터 전달
			SelectBox->AddChild(Button);
		}
		{
			Species = GetNextSpecies(Species);
			if (Species == ESpecies::None) { break; }
		}
	}
}
