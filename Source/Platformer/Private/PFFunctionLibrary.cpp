// Copyright Fillipe Romero

#include "PFFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPFFunctionLibrary::PlayBlockInteractFX(const UObject* WorldContextObject, USoundBase* SoundEffect, UNiagaraSystem* BlockEffect, UParticleSystem* ParticleEffect, FVector EffectLocation)
{
	if (SoundEffect)
		UGameplayStatics::PlaySound2D(WorldContextObject, SoundEffect);

	if (BlockEffect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, BlockEffect, EffectLocation);

	if (ParticleEffect)
		UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, ParticleEffect, EffectLocation);
}
