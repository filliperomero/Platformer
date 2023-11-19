// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFPickupBase.h"
#include "PFCoinPickup.generated.h"

UCLASS()
class PLATFORMER_API APFCoinPickup : public APFPickupBase
{
	GENERATED_BODY()

public:
	APFCoinPickup();
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	int32 AmountOfCoins { 1 };
};
