// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SplineCameraChildActorComponent.h"
#include "Data/PawnTableRow.h"

#include "Actor/BaseCameraSplineActor.h"

                                                             
// Sets default values
USplineCameraChildActorComponent::USplineCameraChildActorComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetChildActorClass(ABaseCameraSplineActor::StaticClass());
	
}


void USplineCameraChildActorComponent::SetData(UClass* NewClass)
{
	if (GetChildActorClass() != NewClass)
	{
		SetChildActorClass(NewClass);
	}


	//ABaseCameraSplineActor* ACameraSplineActor = Cast<ABaseCameraSplineActor>(GetChildActor());
	//check(ACameraSplineActor);
	//APawn* OwnerPawn = Cast<APawn>(GetOwner());
	//check(OwnerPawn);
	//ACameraSplineActor->SetOwner(OwnerPawn);
	//ACameraSplineActor->SetInstigator(OwnerPawn);
}

