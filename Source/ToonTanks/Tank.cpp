// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Chaos/DebugDrawQueue.h"

ATank::ATank()
{
	// Creating various components for the Tank
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	//Init Movement properties
	DeltaLocation = FVector::ZeroVector;
	DeltaRotation = FRotator::ZeroRotator;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binding input controller
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;

		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		// Debug Code for cursor
		 
		//DrawDebugSphere(
		//	GetWorld(),
		//	HitResult.ImpactPoint,
		//	10.f,
		//	12,
		//	FColor::Green
		//);

		ABasePawn::RotateTurret(HitResult.ImpactPoint);
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	// We make the player invisible to be able to see the camera
	// And we remove Tick so no game cycle is available for the player
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::Move(float Value)
{
	// UE_LOG(LogTemp, Display, TEXT("La velovidad es de %f"), Value);

	// Adding movement forward
	DeltaLocation.X = Value * TankSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);	
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	// Adding Value into the delta rotation
	DeltaRotation.Yaw = Value * TankTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}