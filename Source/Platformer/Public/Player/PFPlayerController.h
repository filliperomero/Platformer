﻿// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PFPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32 /*StatValue*/)

UCLASS()
class PLATFORMER_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void AddCoins(int32 InCoins);
	void AddPoints(int32 InPoints);
	void AddLives(int32 InLives);

	FOnPlayerStatChangedSignature OnCoinsChangedDelegate;
	FOnPlayerStatChangedSignature OnLivesChangedDelegate;
	FOnPlayerStatChangedSignature OnPointsChangedDelegate;
	FOnPlayerStatChangedSignature OnLevelTimeChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	TObjectPtr<USoundBase> ReceiveLiveSound;
	
private:
	UPROPERTY(VisibleAnywhere)
	int32 Coins = 0;

	UPROPERTY(VisibleAnywhere)
	int32 Lives = 3;

	UPROPERTY(VisibleAnywhere)
	int32 Points = 0;

	UPROPERTY(VisibleAnywhere)
	int32 LevelTime = 0;

public:
	FORCEINLINE int32 GetCoins() const { return Coins; }
	FORCEINLINE int32 GetLives() const { return Lives; }
	FORCEINLINE int32 GetPoints() const { return Points; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetLevelTime() const { return LevelTime; }
};
