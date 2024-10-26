// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NativeWidgetHost.h"
#include "USelectableCell.generated.h"

/**
 * 
 */
class SSelectableCell;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddPawn, ESpecies, Species, UImage*, Portrait);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReleasedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverEvent);

UCLASS()
class ATB_ROGUE_API USelectableCell : public UNativeWidgetHost
{
	GENERATED_BODY()
	
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	void ReleaseSlateResources(bool bReleaseChildren);

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnClickedEvent OnClicked;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnPressedEvent OnPressed;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnReleasedEvent OnReleased;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHoverEvent OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnHoverEvent OnUnhovered;

	public:
	UPROPERTY()
	FAddPawn AddPawn;

	ESpecies Species;
	UImage* Image;

protected:
	void SlateHandlePressed();
	void SlateHandleReleased();
	void SlateHandleHovered();
	void SlateHandleUnhovered();

	TSharedPtr<SSelectableCell> Cell;
	
	
};
