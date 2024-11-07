// Fill out your copyright notice in the Description page of Project Settings.


#include "Nav/PawnNearNavArea.h"

UPawnNearNavArea::UPawnNearNavArea(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DrawColor = FColor(255, 1, 255);	// brownish
	DefaultCost = 50.f;
}