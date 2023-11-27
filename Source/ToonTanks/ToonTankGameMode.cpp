// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"


void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}


void AToonTankGameMode::ActorDied(AActor* ActorDied)
{
	if (ActorDied == Tank)
	{
		Tank->HandleDestruction();

		if (APlayerController* TankController = Tank->GetTankPlayerController())
		{
			Tank->DisableInput(TankController);
			TankController->bShowMouseCursor = false;
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(ActorDied))
	{
		DestroyedTower->HandleDestruction();
	}
}
