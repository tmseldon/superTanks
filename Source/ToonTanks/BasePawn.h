// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FName PawnTag = "defaultTag";

protected:
	void RotateTurret(FVector LookAtTarget);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Pawn", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Pawn", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Pawn", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Customize Pawn", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
};
