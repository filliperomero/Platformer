// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class APFPlatformBase;

UINTERFACE(MinimalAPI, BlueprintType)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class PLATFORMER_API IPlayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateOverlappingPlatform(APFPlatformBase* Platform);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToCoins(int32 InCoins);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddHitPoints(int32 InHitPoints);
};
