// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/FriendlySpawnLocation.h"

void AFriendlySpawnLocation::Destroyed()
{
	Super::Destroyed();

#if WITH_EDITOR
	if (GIsEditor && !FApp::IsGame())
	{
		for (ASpawnTransform* CurSpawnLocation : FriendlySpawnLocation)
		{
			if (CurSpawnLocation)
			{
				CurSpawnLocation->Destroy();
			}
		}
	}

}
void AFriendlySpawnLocation::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	const FString PropertyName = PropertyAboutToChange->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, FriendlySpawnLocation))
	{
		PrevFriendlySpawnLocation = FriendlySpawnLocation;
	}
}

void AFriendlySpawnLocation::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (GIsEditor && !FApp::IsGame()) {
		PrevFriendlySpawnLocation = FriendlySpawnLocation;
		for (uint8 Index = 0; Index < PrevFriendlySpawnLocation.Num(); Index++)
		{
			FriendlySpawnLocation[Index] = AddSpawnTransform(PrevFriendlySpawnLocation[Index]);
		}
		PrevFriendlySpawnLocation.Empty();
	}
}

void AFriendlySpawnLocation::PostLoad()
{
	Super::PostLoad();
}

void AFriendlySpawnLocation::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AFriendlySpawnLocation::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
void AFriendlySpawnLocation::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FString PropertyName = PropertyChangedEvent.Property->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, FriendlySpawnLocation))
	{
		const int32 Index = PropertyChangedEvent.GetArrayIndex(PropertyName);
		switch (PropertyChangedEvent.ChangeType)
		{
		case EPropertyChangeType::ArrayAdd:
		{
			FriendlySpawnLocation[Index] = AddSpawnTransform();
			break;
		}
		case EPropertyChangeType::ArrayRemove:
		{
			if (PrevFriendlySpawnLocation[Index])
			{
				ASpawnTransform* PrevSpawnLocation = PrevFriendlySpawnLocation[Index];
				PrevSpawnLocation->Destroy();
			}
			break;
		}
		case EPropertyChangeType::Duplicate:
		{
			if (PrevFriendlySpawnLocation[Index])
			{
				FriendlySpawnLocation[Index] = AddSpawnTransform(PrevFriendlySpawnLocation[Index]);
			}
			break;
		}
		case EPropertyChangeType::ArrayClear:
		{
			for (ASpawnTransform* PrevSpawnLocation : PrevFriendlySpawnLocation)
			{
				if (PrevSpawnLocation)
				{
					PrevSpawnLocation->Destroy();
				}
			}
			break;
		}
		default:
			check(false);
			break;
		}
		PrevFriendlySpawnLocation.Empty();
	}
}

ASpawnTransform* AFriendlySpawnLocation::AddSpawnTransform(ASpawnTransform* InTemplate)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters ActorSpawnParameters;
	//ActorSpawnParameters.Owner = this;
	ActorSpawnParameters.Template = InTemplate;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
	const FTransform NewTransform = InTemplate ? InTemplate->GetTransform() :GetActorTransform();
	ASpawnTransform* NewSpawnLocation = World->SpawnActor<ASpawnTransform>(ASpawnTransform::StaticClass(), NewTransform, ActorSpawnParameters);
		NewSpawnLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	return NewSpawnLocation;
}
#endif
TArray<FTransform> AFriendlySpawnLocation::GetSpawnTransform()
{
	TArray<FTransform> ReturnTransform;

	for (int i = 0; i < FriendlySpawnLocation.Num(); i++)
	{
		//보유한 트랜스폼 1~10번까지
		if (FriendlySpawnLocation.IsValidIndex(i))
		{
			ReturnTransform.Add(FriendlySpawnLocation[i]->GetTransform());
		}
	}

	return ReturnTransform;
}