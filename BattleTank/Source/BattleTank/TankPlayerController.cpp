// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	
	if (!ensure(AimingComponent)) { return; }
		
	FoundAimingComponent(AimingComponent);


	auto ControlledTank = GetPawn();

	if (!ensure(ControlledTank)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Playercontroller not posessing a Tank!"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>(); // ->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT Parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	
	if (bGotHitLocation)
	{
		AimingComponent->AimAt(HitLocation);
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	/// find crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	FVector LookDirection;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/// LineTrace along that LookDirection and see if we hit something
		/// GetLookVectorHitLocation
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	/// deproject the screen position of the crosshair to a world direction
	/// line trace along the direction

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const
{
	FVector WorldLocation; // Will be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		//subscribe method to tank broadcast
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);

	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("I AM DED"))
	//StartSpectatingOnly();
}