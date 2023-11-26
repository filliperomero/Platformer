// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFBlockBase.h"
#include "PFFakeBreakableBlock.generated.h"

UCLASS()
class PLATFORMER_API APFFakeBreakableBlock : public APFBlockBase
{
	GENERATED_BODY()

public:
	APFFakeBreakableBlock();

protected:
	virtual void BeginPlay() override;
	virtual void HitBlock(AActor* TargetActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AnimateBlock();

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TSubclassOf<AActor> CoinToSpawn;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<USoundBase> NotAbleToInteractSound;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	int32 MaxAmountOfInteract = 1;

private:
	int32 AmountOfInteract = 0;
};
