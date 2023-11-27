// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Parameters", meta = (AllowPrivateAccess = "true"))
	float MaxTowerDetectingRange = 300.f;

	float MaxSquaredDetectingRange;
	class ATank* PlayerTank;

	bool bIsPlayerInRange();

	// Shooting related private members
	FTimerHandle FireRateTimeHandler;
	float FireRateSeconds = 2.f;
	void CheckFireConditions();
};
