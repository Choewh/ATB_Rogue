	// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SpawnTransform.h"

// Sets default values
ASpawnTransform::ASpawnTransform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Tags.Add(FName("RoundTransform"));
	DefaultComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComponent"));
	RootComponent = DefaultComponent;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	SetActorHiddenInGame(true);
}