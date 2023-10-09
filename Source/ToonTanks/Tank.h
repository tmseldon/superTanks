// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	//Constructor for the tank
	ATank();

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	void Move(float Value);
};



