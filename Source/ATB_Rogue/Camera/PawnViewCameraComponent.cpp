// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PawnViewCameraComponent.h"
#include "Subsystem/BattleSubsystem.h"
#include "Kismet/KismetMathLibrary.h"

UPawnViewCameraComponent::UPawnViewCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/BluePrint/Component/CV_CameraSpline.CV_CameraSpline'"));
	check(CurveAsset.Object);

	//SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	CameraSplineTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("CameraSplineTimelineComponent"));
	CameraSplineTimelineComponent->SetFloatCurve(CurveAsset.Object, TEXT("CameraSplineCurve"));
	CameraSplineTimelineComponent->SetPlayRate(0.1f);

	FOnTimelineFloat Delegate;
	Delegate.BindDynamic(this, &ThisClass::StartSplineMoving);

	CameraSplineTimelineComponent->AddInterpFloat(CurveAsset.Object, Delegate);
	CameraSplineTimelineComponent->SetLooping(true);
}

void UPawnViewCameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPawnViewCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bView && GetWorld()->GetSubsystem<UBattleSubsystem>()->IsValidActionPawn())
	{
		{
			FVector StartVec = GetRelativeLocation();
			FVector TargetVec = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn()->GetActorLocation();


			FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);
			SetRelativeRotation(LookAtRotator);
		}
		{
			//CameraSplineTimelineComponent->TickComponent(DeltaTime, TickType, ThisTickFunction);
		}
	}
}

void UPawnViewCameraComponent::OnPawnViewCamera(ABasePawn* ViewEnemy)
{
	if (ViewEnemy)
	{
		CameraSplineTimelineComponent->PlayFromStart();
	}
}

void UPawnViewCameraComponent::StartSplineMoving(float InDissolve)
{
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	if (bView && BattleSubsystem->IsValidActionPawn())
	{
		{
			FVector StartVec = GetRelativeLocation();
			FVector TargetVec = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn()->GetActorLocation();


			FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);
			SetRelativeRotation(LookAtRotator);
		}
		ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
		AActor* tmepSpline = ActionPawn->GetCameraSpline()->GetChildActor();
		ABaseCameraSplineActor* CameraSplineActor = Cast<ABaseCameraSplineActor>(tmepSpline);
		USplineComponent* CameraSpline = CameraSplineActor->GetPaths();


		FVector Center = ActionPawn->GetActorLocation();
		float SplineLength = CameraSpline->GetSplineLength();

		float Distance = UKismetMathLibrary::Lerp(0.f, SplineLength, InDissolve);

		FVector NewLocation = CameraSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		FRotator NewRotation = CameraSpline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

		SetWorldTransform(FTransform(NewRotation, NewLocation));
	}
}
