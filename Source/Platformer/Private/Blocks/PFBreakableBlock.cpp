// Copyright Fillipe Romero

#include "Blocks/PFBreakableBlock.h"

#include "PFFunctionLibrary.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

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

	if (!IPlayerInterface::Execute_CanBreakBlock(TargetActor))
	{
		if (NotAbleToBreakSound) UGameplayStatics::PlaySound2D(this, NotAbleToBreakSound);
		
		AnimateBlock();

		return;
	}
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, GetActorLocation());
	
	ShowFloatingPoints(TargetActor);

	IPlayerInterface::Execute_AddToPoints(TargetActor, AmountOfPoints);

	Destroy();
}
