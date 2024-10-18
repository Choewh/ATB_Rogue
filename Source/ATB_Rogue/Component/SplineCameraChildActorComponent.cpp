// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SplineCameraChildActorComponent.h"
#include "Data/DataTableRows.h"

#include "Actor/BaseCameraSplineActor.h"


// Sets default values
USplineCameraChildActorComponent::USplineCameraChildActorComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetChildActorClass(ABaseCameraSplineActor::StaticClass());
}

void USplineCameraChildActorComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	FPawnTableRow* Data = InDataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Pawn"));
	if (!Data->CameraSplineClass) { ensure(false); return; }

	//if (GetChildActorClass() != Data->CameraSplineClass)
	//{
	//	SetChildActorClass(Data->CameraSplineClass);
//	}

	if (GetChildActorClass() != Data->CameraSplineClass)
	{
		SetChildActorClass(Data->CameraSplineClass);
	}


	ABaseCameraSplineActor* ACameraSplineActor = Cast<ABaseCameraSplineActor>(GetChildActor());
	check(ACameraSplineActor);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	ACameraSplineActor->SetOwner(OwnerPawn);
	ACameraSplineActor->SetInstigator(OwnerPawn);
}

