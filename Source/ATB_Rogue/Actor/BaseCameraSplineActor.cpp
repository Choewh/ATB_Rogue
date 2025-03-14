// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseCameraSplineActor.h"


// Sets default values
ABaseCameraSplineActor::ABaseCameraSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	//Script/Engine.Blueprint'/Game/BluePrint/Component/BP_Spline.BP_Spline'
	//DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	//RootComponent = DefaultScene;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	//SplineComponent->SetupAttachment(RootComponent);
	RootComponent = SplineComponent;
}

// Called when the game starts or when spawned
void ABaseCameraSplineActor::BeginPlay()
{
	Super::BeginPlay();
	OwningPawn = Cast<APawn>(GetOwner());
}

// Called every frame
void ABaseCameraSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

