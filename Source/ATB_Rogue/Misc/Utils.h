#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
};