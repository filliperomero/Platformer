// Copyright Fillipe Romero

#include "Blocks/PFBreakableBlock.h"

#include "PFFunctionLibrary.h"
#include "Interface/PlayerInterface.h"

APFBreakableBlock::APFBreakableBlock()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APFBreakableBlock::BeginPlay()
{
	Super::BeginPlay();
}

void APFBreakableBlock::HitBlock(AActor* TargetActor)
{
	Super::HitBlock(TargetActor);

	FVector Location = GetActorLocation();
	Location.Z += 50;
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, Location);
	
	ShowFloatingPoints(TargetActor);

	IPlayerInterface::Execute_AddToPoints(TargetActor, AmountOfPoints);

	Destroy();
}
