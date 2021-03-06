// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming, 
	Reloading,
	OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;
class UAudioComponent;

// Hold barrel properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	bool IsBarrelMoving();

	void MoveBarrelTowards(FVector AimDirection);

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoCount() const;

private:


	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000; 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 3;

	double LastFireTime = 0;
	FVector AimDirection;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;
		
};
