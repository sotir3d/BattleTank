// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *AIForwardIntention.ToString())

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(TurnThrow);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
