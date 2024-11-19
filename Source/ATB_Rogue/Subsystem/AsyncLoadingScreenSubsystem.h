// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AsyncLoadingScreenSubsystem.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class ATB_ROGUE_API UAsyncLoadingScreenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void OpenLevelWithLoadingScreen(TSubclassOf<UUserWidget> WidgetClass, const TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintCallable)
	void NextLevelOpen();

	UUserWidget* LoadingScreenWidget;
	TSoftObjectPtr<UWorld> OpenLevel;
};
