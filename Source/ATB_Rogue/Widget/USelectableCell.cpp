// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/USelectableCell.h"
#include "Widget/SSelectableCell.h"

TSharedRef<SWidget> USelectableCell::RebuildWidget()
{
    Cell = SNew(SSelectableCell)
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        .OnPressedArg_UObject(this, &ThisClass::SlateHandlePressed)
        .OnReleasedArg(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
        .OnHoveredArg_UObject(this, &ThisClass::SlateHandleHovered)
        .OnUnhoveredArg_UObject(this, &ThisClass::SlateHandleUnhovered)
        ;
    return Cell.ToSharedRef();
}

void USelectableCell::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Cell.Reset();
}

void USelectableCell::SlateHandlePressed()
{
    OnPressed.Broadcast();
    AddPawn.Broadcast(Species, Image);
}

void USelectableCell::SlateHandleReleased()
{

}

void USelectableCell::SlateHandleHovered()
{
}

void USelectableCell::SlateHandleUnhovered()
{
}
