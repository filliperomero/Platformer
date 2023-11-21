// Copyright Fillipe Romero

#include "UI/WidgetController/PFWidgetController.h"

#include "Player/PFPlayerController.h"

void UPFWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
}

void UPFWidgetController::BroadcastInitialValues()
{
}

void UPFWidgetController::BindCallbacksToDependencies()
{
}

APFPlayerController* UPFWidgetController::GetPFPC()
{
	if (PFPlayerController == nullptr)
	{
		PFPlayerController = Cast<APFPlayerController>(PlayerController);
	}

	return PFPlayerController;
}
