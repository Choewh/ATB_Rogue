#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enums/Species.h"

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
		FString RoundString	= FString::Printf(TEXT("Round%d"), Round);
		FName RoundName(*RoundString);
		return RoundName;
	}
	// ESpecies를 넣으면 Display 네임으로 바꿔주는거
	static const FText  GetSpeciesName(ESpecies InSpecies)
	{
		UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESpecies"), true);
		if (EnumPtr)
		{
			// Enum 값을 기반으로 DisplayName을 가져옴
			return EnumPtr->GetDisplayNameTextByValue(static_cast<int32>(InSpecies));
		}
		return FText(); // 유효하지 않을 경우 빈 FText 반환
	}
};