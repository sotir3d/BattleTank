// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn * InPawn) override;


private:
	//how close can the AI Tank get
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 5000;

	UFUNCTION()
	void OnTankDeath();

};
