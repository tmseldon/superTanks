// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"


void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleStartGame();
}


void AToonTankGameMode::ActorDied(AActor* ActorDied)
{
	if (ActorDied == Tank)
	{
		Tank->HandleDestruction();

		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(ActorDied))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		
		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTankGameMode::HandleStartGame()
{
	TargetTowers = GetTowerTargetCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//Calling Blueprint Event
	StartGame();

	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);
	
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, SecondsToStartGame, false);
	}
}

int32 AToonTankGameMode::GetTowerTargetCount()
{
	TArray<AActor*> CurrentTowers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), CurrentTowers);
	return CurrentTowers.Num();
}
