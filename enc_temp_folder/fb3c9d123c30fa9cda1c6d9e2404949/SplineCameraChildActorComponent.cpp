// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SplineCameraChildActorComponent.h"

#include "Actor/BaseCameraSplineActor.h"


// Sets default values
USplineCameraChildActorComponent::USplineCameraChildActorComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetChildActorClass(ABaseCameraSplineActor::StaticClass());
}

void USplineCameraChildActorComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	//if (InDataTableRowHandle.IsNull()) { return; }
	//FWeaponTableRow* Data = InDataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	//if (!Data) { ensure(false); return; }

	//if (GetChildActorClass() != Data->WeaponClass)
	//{
	//	SetChildActorClass(Data->WeaponClass);
	//}

	//AWeaponBase* Weapon = Cast<AWeaponBase>(GetChildActor());
	//check(Weapon);
	//APawn* OwnerPawn = Cast<APawn>(GetOwner());
	//check(OwnerPawn);
	//Weapon->SetOwner(OwnerPawn);
	//Weapon->SetInstigator(OwnerPawn);
	//Weapon->SetData(InDataTableRowHandle);

}

void USplineCameraChildActorComponent::SetData()
{
	ABaseCameraSplineActor* ACameraSplineActor = Cast<ABaseCameraSplineActor>(GetChildActor());
	check(ACameraSplineActor);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	ACameraSplineActor->SetOwner(OwnerPawn);
	ACameraSplineActor->SetInstigator(OwnerPawn);
}

