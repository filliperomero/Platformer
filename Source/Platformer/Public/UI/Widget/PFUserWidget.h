// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PFUserWidget.generated.h"

UCLASS()
class PLATFORMER_API UPFUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
