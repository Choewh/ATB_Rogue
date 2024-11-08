// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Subsystem/BattleSubsystem.h"
#include "Subsystem/ATBGameInstanceSubsystem.h"
#include "GameMode/BasePlayerController.h"

#include "ATBUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UATBUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	friend class AATBHUD;

public:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	void SetOwningPawn(APawn* NewPawn) { OwningPawn = NewPawn; }
	APawn* GetOwningPawn() const { return OwningPawn; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ABasePlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBattleSubsystem* BattleSubsystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UATBGameInstanceSubsystem* ATBGameInstanceSubsystem;

	UPROPERTY()
	APawn* OwningPawn = nullptr;
};
