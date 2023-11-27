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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	// Getter for the Tank Player Controller
	// For now used by ToonTank Game Mode
	APlayerController* GetTankPlayerController() const { return TankPlayerController; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector DeltaLocation;
	FRotator DeltaRotation;

	APlayerController* TankPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Parameters", meta = (AllowPrivateAccess = "true"))
	float TankSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Parameters", meta = (AllowPrivateAccess = "true"))
	float TankTurnRate = 100.f;

	void Move(float Value);

	void Turn(float Value);
};



