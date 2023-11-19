// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PFPlayerController.generated.h"

UCLASS()
class PLATFORMER_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AddCoins(int32 InCoins);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	TObjectPtr<USoundBase> ReceiveLiveSound;

private:
	UPROPERTY(VisibleAnywhere)
	int32 Coins { 0 };

	UPROPERTY(VisibleAnywhere)
	int32 Lives { 3 };

public:
	FORCEINLINE int32 GetCoins() const { return Coins; }
	FORCEINLINE int32 GetLives() const { return Lives; }
};
