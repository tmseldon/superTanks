// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool bIsPlayerEnabled)
{
	if (bIsPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bIsPlayerController;
}
