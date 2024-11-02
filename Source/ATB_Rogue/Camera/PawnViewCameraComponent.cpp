// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PawnViewCameraComponent.h"
#include "Subsystem/BattleSubsystem.h"
#include "Kismet/KismetMathLibrary.h"

UPawnViewCameraComponent::UPawnViewCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CurveAsset(TEXT("/Script/Engine.CurveFloat'/Game/BluePrint/Component/CV_CameraSpline.CV_CameraSpline'"));
	check(CurveAsset.Object);

	CameraSplineTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("CameraSplineTimelineComponent"));

	//CameraSplineTimelineComponent->SetFloatCurve(CurveAsset.Object, TEXT("CameraSplineCurve"));
	CameraSplineTimelineComponent->SetPlayRate(0.2f);

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

}

void UPawnViewCameraComponent::OnPawnViewCamera(ABasePawn* ViewEnemy)
{
	if (ViewEnemy)
	{
		FVector StartVec = GetComponentLocation();
		FVector TargetVec = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn()->GetActorLocation();


		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);
		SetWorldRotation(LookAtRotator);
		CameraSplineTimelineComponent->PlayFromStart();
	}
}

void UPawnViewCameraComponent::StartSplineMoving(float InDissolve)
{
	UBattleSubsystem* BattleSubsystem = GetWorld()->GetSubsystem<UBattleSubsystem>();
	if (bView && BattleSubsystem->IsValidActionPawn())
	{

			ABasePawn* ActionPawn = BattleSubsystem->GetActionPawn();
			AActor* tmepSpline = ActionPawn->GetCameraSpline()->GetChildActor();
			ABaseCameraSplineActor* CameraSplineActor = Cast<ABaseCameraSplineActor>(tmepSpline);
			USplineComponent* CameraSpline = CameraSplineActor->GetPaths();

		{
			//FVector Center = ActionPawn->GetActorLocation();
			float SplineLength = CameraSpline->GetSplineLength();

			float Distance = UKismetMathLibrary::Lerp(0.f, SplineLength, InDissolve);

			FVector SplineLocation = CameraSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			FRotator SplineRotation = CameraSpline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

			SetWorldTransform(FTransform(SplineRotation, SplineLocation));
		}
		{
			FVector StartVec = GetComponentLocation();
			FVector TargetVec = GetWorld()->GetSubsystem<UBattleSubsystem>()->GetActionPawn()->GetActorLocation();

			FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(StartVec, TargetVec);
			SetWorldRotation(LookAtRotator);
		}
	}
}

