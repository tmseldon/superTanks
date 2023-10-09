// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
	// Creating various components for the Tank
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}


void ATank::Move(float Value)
{
	UE_LOG(LogTemp, Display, TEXT("La velovidad es de %f"), Value);
}