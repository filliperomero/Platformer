// Copyright Fillipe Romero

#include "Player/PFPlayerController.h"
#include "Kismet/GameplayStatics.h"

void APFPlayerController::AddCoins(int32 InCoins)
{
	if (InCoins <= 0) return;

	const int32 NewCoins = Coins + InCoins;

	if (NewCoins >= 100)
	{
		Coins = FMath::Clamp(NewCoins - 100, 0, 100);
		AddLives(1);
		if (ReceiveLiveSound) UGameplayStatics::PlaySound2D(this, ReceiveLiveSound);
	}
	else
	{
		Coins = FMath::Clamp(NewCoins, 0, 100);
	}

	OnCoinsChangedDelegate.Broadcast(Coins);
}

void APFPlayerController::AddPoints(int32 InPoints)
{
	Points += InPoints;
	OnPointsChangedDelegate.Broadcast(Points);
}

void APFPlayerController::AddLives(int32 InLives)
{
	Lives = FMath::Clamp(Lives + InLives, 0, 100);
	OnLivesChangedDelegate.Broadcast(Lives);

	if (Lives == 0)
	{
		UGameplayStatics::OpenLevel(this, FName("LV_MainMenu"));
	}
}
