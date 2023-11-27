// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// Getting the player reference
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Init variables
	MaxSquaredDetectingRange = powf(MaxTowerDetectingRange, 2);
	
	GetWorldTimerManager().SetTimer(
		FireRateTimeHandler,
		this,
		&ATower::CheckFireConditions,
		FireRateSeconds,
		true
	);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPlayerInRange())
	{
		// Rotate the tower towards the player
		ABasePawn::RotateTurret(PlayerTank->GetActorLocation());
	}
}

void ATower::CheckFireConditions()
{
	if (bIsPlayerInRange())
	{
		ABasePawn::Fire();
	}
}

// Helper method to check if the player is on range of shooting
bool ATower::bIsPlayerInRange()
{
	if (PlayerTank)
	{
		// Calculate the squared distance, it is easier for calculations to get the squared distance
		float SquaredDistanceToTank = FVector::DistSquared(GetActorLocation(), PlayerTank->GetActorLocation());

		// Check if it is on range
		if (SquaredDistanceToTank < MaxSquaredDetectingRange)
		{
			return true;
		}
	}

	return false;
}