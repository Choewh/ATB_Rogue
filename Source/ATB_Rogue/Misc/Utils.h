#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enums/Species.h"
#include "Enums/Stage.h"
#include "Enums/SelectAbleSpecies.h"


namespace CollisionProfileName
{
	static inline FName PawnTrigger = TEXT("Round_1");
	static inline FName PlayerTrigger = TEXT("Round_2");
	static inline FName Player = TEXT("Player");
	static inline FName Enemy = TEXT("Enemy");
	static inline FName Projectile = TEXT("Projectile");
}

class FUtils
{
public:
	static const UInputAction* GetInputActionFromName(UInputMappingContext* InputMappingContext, const FName& Name)
	{
		const TArray<FEnhancedActionKeyMapping> Mappings = InputMappingContext->GetMappings();
		for (auto& it : Mappings)
		{
			if (it.Action.GetFName() == Name)
			{
				return it.Action.Get();
			}
		}
		return nullptr;
	}
	static const FName Round(uint8 Round)
	{
		FString RoundString = FString::Printf(TEXT("Round%d"), Round);
		FName RoundName(*RoundString);
		return RoundName;
	}
	static const FName GetTextPlusInt(FString InString, uint8 Inint)
	{
		FString StringAddInt = FString::Printf(TEXT("%s%d"), *InString, Inint);
		FName Result(*StringAddInt);
		return Result;
	}
	// ESpecies를 넣으면 Display 네임으로 바꿔주는거
	static const FText  GetSpeciesName(ESpecies InSpecies)
	{
		// UEnum 객체를 가져옴.
		UEnum* EnumPtr = StaticEnum<ESpecies>();
		if (EnumPtr)
		{
			// Enum 값에 해당하는 DisplayName을 FText로 반환
			return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(InSpecies));
		}
		return FText::FromString("Invalid");
	}
	static const FText  GetStageName(EStage InStage)
	{
		// UEnum 객체를 가져옵니다.
		UEnum* EnumPtr = StaticEnum<EStage>();
		if (EnumPtr)
		{
			// Enum 값에 해당하는 DisplayName을 FText로 반환
			return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(InStage));
		}
		return FText::FromString("Invalid");
	}
};