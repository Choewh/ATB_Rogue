// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseFloatingPawnMovement.h"

float GetAxisDeltaRotation2(float InAxisRotationRate, float DeltaTime)
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}


FRotator UBaseFloatingPawnMovement::GetDeltaRotation(float DeltaTime) const
{
	return FRotator(GetAxisDeltaRotation2(RotationRate.Pitch, DeltaTime), GetAxisDeltaRotation2(RotationRate.Yaw, DeltaTime), GetAxisDeltaRotation2(RotationRate.Roll, DeltaTime));
}


UBaseFloatingPawnMovement::UBaseFloatingPawnMovement()
	: bOrientRotationToMovement(true)
{

	RotationRate = FRotator(0.f, 360.0f, 0.0f);

}

void UBaseFloatingPawnMovement::PhysicsRotation(float DeltaTime)
{
	if (!bOrientRotationToMovement) { return; }

	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation(); // Normalized
	CurrentRotation.DiagnosticCheckNaN(TEXT("UAdvenceFloatingPawnMovement::PhysicsRotation(): CurrentRotation"));

	FRotator DeltaRot = GetDeltaRotation(DeltaTime);
	DeltaRot.DiagnosticCheckNaN(TEXT("UAdvenceFloatingPawnMovement::PhysicsRotation(): GetDeltaRotation"));

	FRotator DesiredRotation = CurrentRotation;
	if (bOrientRotationToMovement)
	{
		DesiredRotation = ComputeOrientToMovementRotation(CurrentRotation, DeltaTime, DeltaRot);
	}

	// const bool bWantsToBeVertical = ShouldRemainVertical();
	{
		DesiredRotation.Pitch = 0.f;
		DesiredRotation.Yaw = FRotator::NormalizeAxis(DesiredRotation.Yaw);
		DesiredRotation.Roll = 0.f;
	}

	// Accumulate a desired new rotation.
	const float AngleTolerance = 1e-3f;
	if (!CurrentRotation.Equals(DesiredRotation, AngleTolerance))
	{
		// If we'd be prevented from becoming vertical, override the non-yaw rotation rates to allow the character to snap upright
		//if (CharacterMovementCVars::bPreventNonVerticalOrientationBlock && bWantsToBeVertical)
		{
			if (FMath::IsNearlyZero(DeltaRot.Pitch))
			{
				DeltaRot.Pitch = 360.0;
			}
			if (FMath::IsNearlyZero(DeltaRot.Roll))
			{
				DeltaRot.Roll = 360.0;
			}
		}

		{
			// PITCH
			if (!FMath::IsNearlyEqual(CurrentRotation.Pitch, DesiredRotation.Pitch, AngleTolerance))
			{
				DesiredRotation.Pitch = FMath::FixedTurn(CurrentRotation.Pitch, DesiredRotation.Pitch, DeltaRot.Pitch);
			}

			// YAW
			if (!FMath::IsNearlyEqual(CurrentRotation.Yaw, DesiredRotation.Yaw, AngleTolerance))
			{
				DesiredRotation.Yaw = FMath::FixedTurn(CurrentRotation.Yaw, DesiredRotation.Yaw, DeltaRot.Yaw);
			}

			// ROLL
			if (!FMath::IsNearlyEqual(CurrentRotation.Roll, DesiredRotation.Roll, AngleTolerance))
			{
				DesiredRotation.Roll = FMath::FixedTurn(CurrentRotation.Roll, DesiredRotation.Roll, DeltaRot.Roll);
			}
		}
		// Set the new rotation.
		DesiredRotation.DiagnosticCheckNaN(TEXT("UAdvanceFloatingPawnMovement::PhysicsRotation(): DesiredRotation"));
		MoveUpdatedComponent(FVector::ZeroVector, DesiredRotation, /*bSweep*/ false);
	}
}

FRotator UBaseFloatingPawnMovement::ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const
{
	{
		if (AccelerationAdvance.SizeSquared() < UE_KINDA_SMALL_NUMBER)
		{
			// AI path following request can orient us in that direction (it's effectively an acceleration)
			//if (bHasRequestedVelocity && RequestedVelocity.SizeSquared() > UE_KINDA_SMALL_NUMBER)
			//{
			//	return RequestedVelocity.GetSafeNormal().Rotation();
			//}

			// Don't change rotation if there is no acceleration.
			return CurrentRotation;
		}

		// Rotate toward direction of acceleration.
		return AccelerationAdvance.GetSafeNormal().Rotation();
	}
}

void UBaseFloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Super::TickComponent를 아래로 옮겨놔서 그 부모의 TickComponent를 호출
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccelerationAdvance = Velocity.GetSafeNormal();

	PhysicsRotation(DeltaTime);

}