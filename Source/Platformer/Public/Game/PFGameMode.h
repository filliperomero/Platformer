// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestPlayerRespawnSignature, AController* /*Controller*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelTimeChangedSignature, int32 /*LevelTimeValue*/)
DECLARE_MULTICAST_DELEGATE(FOnCompleteLevelSignature)

UCLASS(minimalapi)
class APFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APFGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void RequestRespawn(ACharacter* Character, AController* Controller);
	UFUNCTION(BlueprintCallable)
	void SetLevelTime(const float InLevelTime);
	void CompleteLevel();

	FOnRequestPlayerRespawnSignature OnRequestPlayerRespawnDelegate;
	FOnLevelTimeChangedSignature OnLevelTimeChangedDelegate;
	FOnCompleteLevelSignature OnCompleteLevelDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "")
	FTransform SpawnTransform = FTransform();

private:
	UPROPERTY(VisibleAnywhere)
	float InitialLevelTime = 0;

	UPROPERTY(VisibleAnywhere)
	int32 LevelTime = 0;

	UPROPERTY(VisibleAnywhere)
	float StartingTime = 0;

	uint32 CountdownInt = 0;

	bool bStopLevelTime = false;

public:
	FORCEINLINE void SetSpawnTransform(const FTransform& InSpawnTransform) { SpawnTransform = InSpawnTransform; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetLevelTime() const { return LevelTime; }
};



