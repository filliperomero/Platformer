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
		Lives++;
		OnLivesChangedDelegate.Broadcast(Lives);
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
