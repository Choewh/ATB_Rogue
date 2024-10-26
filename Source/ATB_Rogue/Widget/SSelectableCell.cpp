// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SSelectableCell.h"

#include "SlateOptMacros.h"
#include "SSelectableCell.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSelectableCell::Construct(const FArguments& InArgs)
{
	HAlign = InArgs._HAlign;
	VAlign = InArgs._VAlign;
	OnPressed = InArgs._OnPressedArg;
	OnReleased = InArgs._OnReleasedArg;
	OnHovered = InArgs._OnHoveredArg;
	OnUnhovered = InArgs._OnUnhoveredArg;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSelectableCell::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	OnPressed.ExecuteIfBound();
	return FReply::Handled();
}

FReply SSelectableCell::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	OnReleased.ExecuteIfBound();
	return FReply::Handled();
}

void SSelectableCell::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
}

void SSelectableCell::OnMouseLeave(const FPointerEvent& MouseEvent)
{
}
