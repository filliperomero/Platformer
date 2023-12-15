// Copyright Fillipe Romero

#include "UI/WidgetController/PFOverlayWidgetController.h"
#include "Player/PFPlayerController.h"

void UPFOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	OnPlayerCoinsChangedDelegate.Broadcast(GetPFPC()->GetCoins());
	OnPlayerLivesChangedDelegate.Broadcast(GetPFPC()->GetLives());
	OnPlayerPointsChangedDelegate.Broadcast(GetPFPC()->GetPoints());
	OnGameLevelTimeChangedDelegate.Broadcast(GetPFPC()->GetLevelTime());
}

void UPFOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	/** Bind to PlayerController Delegates */
	GetPFPC()->OnCoinsChangedDelegate.AddLambda(
		[this](int32 NewValue)
		{
			OnPlayerCoinsChangedDelegate.Broadcast(NewValue);
		}
	);

	GetPFPC()->OnLivesChangedDelegate.AddLambda(
		[this](int32 NewValue)
		{
			OnPlayerLivesChangedDelegate.Broadcast(NewValue);
		}
	);

	GetPFPC()->OnPointsChangedDelegate.AddLambda(
		[this](int32 NewValue)
		{
			OnPlayerPointsChangedDelegate.Broadcast(NewValue);
		}
	);

	GetPFPC()->OnLevelTimeChangedDelegate.AddLambda(
		[this](int32 NewValue)
		{
			OnGameLevelTimeChangedDelegate.Broadcast(NewValue);
		}
	);
}
