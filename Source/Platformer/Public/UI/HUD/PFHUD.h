// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PFHUD.generated.h"

class UPFOverlayWidgetController;
struct FWidgetControllerParams;
class UPFUserWidget;

UCLASS()
class PLATFORMER_API APFHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPFOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(APlayerController* PC);

private:
	UPROPERTY()
	TObjectPtr<UPFUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPFUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPFOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPFOverlayWidgetController> OverlayWidgetControllerClass;
};
