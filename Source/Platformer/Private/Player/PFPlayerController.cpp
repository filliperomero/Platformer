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
		if (ReceiveLiveSound) UGameplayStatics::PlaySound2D(this, ReceiveLiveSound);
	}
	else
	{
		Coins = FMath::Clamp(NewCoins, 0, 100);
	}

	UE_LOG(LogTemp, Warning, TEXT("Amount of Coins %d and Amount of Lives %d"), Coins, Lives);
}
