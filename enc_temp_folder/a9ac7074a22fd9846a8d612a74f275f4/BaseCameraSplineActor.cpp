// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseCameraSplineActor.h"


// Sets default values
ABaseCameraSplineActor::ABaseCameraSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;
}

// Called when the game starts or when spawned
void ABaseCameraSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCameraSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

