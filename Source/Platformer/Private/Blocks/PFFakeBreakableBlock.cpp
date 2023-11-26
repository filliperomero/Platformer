// Copyright Fillipe Romero

#include "Blocks/PFFakeBreakableBlock.h"
#include "PFFunctionLibrary.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

APFFakeBreakableBlock::APFFakeBreakableBlock()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APFFakeBreakableBlock::BeginPlay()
{
	Super::BeginPlay();
}

void APFFakeBreakableBlock::HitBlock(AActor* TargetActor)
{
	if (AmountOfInteract >= MaxAmountOfInteract)
	{
		if (NotAbleToInteractSound) UGameplayStatics::PlaySound2D(this, NotAbleToInteractSound);

		return;
	}
	
	Super::HitBlock(TargetActor);

	const bool IsLastInteract = AmountOfInteract + 1 >= MaxAmountOfInteract;
	
	FVector Location = GetActorLocation();
	Location.Z += 50;
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, Location);
	
	if (InteractMaterial && IsLastInteract)
		BlockMesh->SetMaterial(0, InteractMaterial);
	
	ShowFloatingPoints(TargetActor);

	IPlayerInterface::Execute_AddToPoints(TargetActor, AmountOfPoints);
	IPlayerInterface::Execute_AddToCoins(TargetActor, AmountOfCoins);

	// For Future: Change this for an Niagara System
	if (CoinToSpawn)
		GetWorld()->SpawnActor<AActor>(CoinToSpawn, GetActorTransform());

	AnimateBlock();
	
	AmountOfInteract++;
}
