﻿// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class APFPlatformBase;

UENUM(BlueprintType)
enum class EPowerUpType
{
	EPT_FlowerPower UMETA(DisplayName = "Flower Power Up")
};

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
	void UpdateOverlappingActor(AActor* InOverlappingActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToCoins(int32 InCoins);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddHitPoints(int32 InHitPoints);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddLives(int32 InLives);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddToPoints(int32 InPoints);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivatePowerUp(const EPowerUpType PowerUpType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanBreakBlock();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LaunchCharacter(const FVector& LaunchVelocity);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayForceFeedback(UForceFeedbackEffect* ForceFeedbackEffect);
};
