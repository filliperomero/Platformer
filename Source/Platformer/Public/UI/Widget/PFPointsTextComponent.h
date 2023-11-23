// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PFPointsTextComponent.generated.h"

UCLASS()
class PLATFORMER_API UPFPointsTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetPointsText(int32 Points);
	
};
