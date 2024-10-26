// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ATB_ROGUE_API SSelectableCell : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSelectableCell)
			:
		_HAlign( HAlign_Fill )
		, _VAlign( VAlign_Fill )
	{
	}
		/** Horizontal alignment */
		SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

		/** Vertical alignment */
		SLATE_ARGUMENT(EVerticalAlignment, VAlign)

		SLATE_EVENT(FSimpleDelegate, OnPressedArg)

		SLATE_EVENT(FSimpleDelegate, OnReleasedArg)

		SLATE_EVENT(FSimpleDelegate, OnHoveredArg)

		SLATE_EVENT(FSimpleDelegate, OnUnhoveredArg)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

private:
	EHorizontalAlignment HAlign;
	EVerticalAlignment VAlign;
	/** The delegate to execute when the button is pressed */
	FSimpleDelegate OnPressed;

	/** The delegate to execute when the button is released */
	FSimpleDelegate OnReleased;

	/** The delegate to execute when the button is hovered */
	FSimpleDelegate OnHovered;

	/** The delegate to execute when the button exit the hovered state */
	FSimpleDelegate OnUnhovered;
};
