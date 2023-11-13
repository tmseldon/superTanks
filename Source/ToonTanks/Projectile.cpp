// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting callback for OnHit Event
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
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

	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr) { return; }

	AController* OwnerInstigatorController = MyOwner->GetInstigatorController();
	UClass* DamageType = UDamageType::StaticClass();

	if (!(OtherActor && OtherActor != this && OtherActor != MyOwner))
	{
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, OwnerInstigatorController, this, DamageType);
	Destroy();
}

