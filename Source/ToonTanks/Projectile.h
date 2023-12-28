// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Projectile", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Params Projectile")
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
	float DamageAmount = 50.f;

	UPROPERTY(EditAnywhere, Category = "Customize Projectile")
	class UParticleSystem* HitParticleFX;

	UPROPERTY(EditAnywhere, Category = "Customize Projectile")
	USoundBase* LaunchProjectileSound;

	UPROPERTY(EditAnywhere, Category = "Customize Projectile")
	USoundBase* ImpactProjectileSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Projectile", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SmokeTrailParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Customize Projectile")
	TSubclassOf<class UCameraShakeBase> ImpactCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
