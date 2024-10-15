#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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

};