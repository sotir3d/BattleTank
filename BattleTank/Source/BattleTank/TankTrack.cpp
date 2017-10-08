// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();

	Throttle = FMath::Clamp<float>(Throttle, -1.0, 1.0);

	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, Throttle)

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}
