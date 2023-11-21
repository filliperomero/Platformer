// Copyright Fillipe Romero

#include "UI/HUD/PFHUD.h"
#include "UI/Widget/PFUserWidget.h"
#include "UI/WidgetController/PFOverlayWidgetController.h"
#include "UI/WidgetController/PFWidgetController.h"

UPFOverlayWidgetController* APFHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UPFOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void APFHUD::InitOverlay(APlayerController* PC)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_PFHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_PFHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UPFUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC);
	UPFOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);

	// Broadcast all Initial Values
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
