// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFGameMode.generated.h"

UCLASS(minimalapi)
class APFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APFGameMode();
	
	void RequestRespawn(ACharacter* Character, AController* Controller);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "")
	FTransform SpawnTransform = FTransform();

public:
	FORCEINLINE void SetSpawnTransform(const FTransform& InSpawnTransform) { SpawnTransform = InSpawnTransform; }
};



