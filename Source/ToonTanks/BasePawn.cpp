// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Creating various components for the Base Pawn
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// Adding FX and sound for destroy here
	if (DeathParticleFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticleFX,
			GetActorLocation(),
			GetActorRotation()
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector RotationDirection = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator NewRotationTurret = FRotator(0.f, RotationDirection.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			NewRotationTurret,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			8.f
		)
	);
}

void ABasePawn::Fire()
{
	// Debug purposes only
	
	//DrawDebugSphere(
	//	GetWorld(),
	//	ProjectileSpawnPoint->GetComponentLocation(),
	//	10.f,
	//	12,
	//	FColor::Red,
	//	false,
	//	3.f
	//);

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileReferenceType,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
		);

	SpawnedProjectile->SetOwner(this);
}