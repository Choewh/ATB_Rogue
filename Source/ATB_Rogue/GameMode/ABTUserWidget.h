// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/BattleSubsystem.h"
#include "GameMode/BasePlayerController.h"
#include "ABTUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UABTUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	friend class AABTHUD;

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ABasePlayerController* PlayerController;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBattleSubsystem* BattleSubsystem;
};
