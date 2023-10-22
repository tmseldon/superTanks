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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;

		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			10.f,
			12,
			FColor::Green
		);
	}

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