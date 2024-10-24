// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/EnemySpawnTransform.h"

void AEnemySpawnTransform::Destroyed()
{
	Super::Destroyed();

#if WITH_EDITOR

	if (GIsEditor && !FApp::IsGame())
	{
		for (ASpawnTransform* CurSpawnLocation : EnemySpawnTransform)
		{
			if (CurSpawnLocation)
			{
				CurSpawnLocation->Destroy();
			}
		}
	}

}

void AEnemySpawnTransform::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	const FString PropertyName = PropertyAboutToChange->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, EnemySpawnTransform))
	{
		PrevEnemySpawnTransform = EnemySpawnTransform;
	}
}

void AEnemySpawnTransform::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (GIsEditor && !FApp::IsGame()) {
		PrevEnemySpawnTransform = EnemySpawnTransform;
		for (uint8 Index = 0; Index < PrevEnemySpawnTransform.Num(); Index++)
		{
			EnemySpawnTransform[Index] = AddSpawnTransform(PrevEnemySpawnTransform[Index]);
		}
		PrevEnemySpawnTransform.Empty();
	}
}

void AEnemySpawnTransform::PostLoad()
{
	Super::PostLoad();
}

void AEnemySpawnTransform::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void AEnemySpawnTransform::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemySpawnTransform::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (GIsEditor && !FApp::IsGame()) {
		const FString PropertyName = PropertyChangedEvent.Property->GetName();
		if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, EnemySpawnTransform))
		{
			const int32 Index = PropertyChangedEvent.GetArrayIndex(PropertyName);
			switch (PropertyChangedEvent.ChangeType)
			{
			case EPropertyChangeType::ArrayAdd:
			{
				EnemySpawnTransform[Index] = AddSpawnTransform();
				break;
			}
			case EPropertyChangeType::ArrayRemove:
			{
				if (PrevEnemySpawnTransform[Index])
				{
					ASpawnTransform* PrevSpawnLocation = PrevEnemySpawnTransform[Index];
					PrevSpawnLocation->Destroy();
				}
				break;
			}
			case EPropertyChangeType::Duplicate:
			{
				if (PrevEnemySpawnTransform[Index])
				{
					EnemySpawnTransform[Index] = AddSpawnTransform(PrevEnemySpawnTransform[Index]);
				}
				break;
			}
			case EPropertyChangeType::ArrayClear:
			{
				for (ASpawnTransform* PrevSpawnLocation : PrevEnemySpawnTransform)
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
			PrevEnemySpawnTransform.Empty();
		}
	}
}

ASpawnTransform* AEnemySpawnTransform::AddSpawnTransform(ASpawnTransform* InTemplate)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters ActorSpawnParameters;
	//ActorSpawnParameters.Owner = this;
	ActorSpawnParameters.Template = InTemplate;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
	const FTransform NewTransform = InTemplate ? InTemplate->GetTransform() : GetActorTransform();
	ASpawnTransform* NewSpawnLocation = World->SpawnActor<ASpawnTransform>(ASpawnTransform::StaticClass(), NewTransform, ActorSpawnParameters);
	NewSpawnLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);


	return NewSpawnLocation;
}
#endif

TArray<FTransform> AEnemySpawnTransform::GetSpawnTransform()
{
	TArray<FTransform> ReturnTransform;
	
	for (int i = 0; i < EnemySpawnTransform.Num(); i++)
	{
		//보유한 트랜스폼 1~10번까지
		if (EnemySpawnTransform.IsValidIndex(i))
		{
			ReturnTransform.Add(EnemySpawnTransform[i]->GetTransform());
		}
	}

	return ReturnTransform;
}