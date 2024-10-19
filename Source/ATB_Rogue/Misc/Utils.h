#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enums/PawnDataHandle.h"
#include "Data/DataTableRows.h"

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

	static const FDataTableRowHandle GetTableRowFromName(const FDataTableRowHandle& InDataTableRowHandle, const EPawnDataHandle PawnDataHandle)
	{
		FPawnTableRow* Data = InDataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Guilmon"));
		if (!Data) { ensure(false); return FDataTableRowHandle(); }
		
		switch (PawnDataHandle)
		{
		case EPawnDataHandle::Effect:
			return Data->Effect;
		case EPawnDataHandle::Stat:
			return Data->Stat;
		default:
			return FDataTableRowHandle();
		}
	}
};