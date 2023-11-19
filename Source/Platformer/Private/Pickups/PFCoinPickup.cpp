// Copyright Fillipe Romero

#include "Pickups/PFCoinPickup.h"

#include "Interface/PlayerInterface.h"

APFCoinPickup::APFCoinPickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APFCoinPickup::BeginPlay()
{
	Super::BeginPlay();
}

void APFCoinPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!OtherActor->Implements<UPlayerInterface>()) return;

	IPlayerInterface::Execute_AddToCoins(OtherActor, AmountOfCoins);

	Destroy();
}


