// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init variables
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	MovementComponent->InitialSpeed = 10.f;
	MovementComponent->MaxSpeed = 100.f;

	//Init Particle Component
	SmokeTrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrailParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting callback for OnHit Event
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchProjectileSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchProjectileSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Callback method when the projectile hits something
void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Probando %s"), *OtherActor->GetName());

	// Reference to the owner so we can get the AController
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr) 
	{ 
		Destroy();
		return; 
	}

	AController* OwnerInstigatorController = MyOwner->GetInstigatorController();
	UClass* DamageType = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, OwnerInstigatorController, this, DamageType);
		
		//All the effects below here

		if (HitParticleFX)
		{
			// We trigger the smoke FX before destroying the missile
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticleFX,
				GetActorLocation(),
				GetActorRotation()
			);
		}

		if (ImpactProjectileSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactProjectileSound, GetActorLocation());
		}

		if (ImpactCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ImpactCameraShakeClass);
		}
	}

	Destroy();
}

