// Copyright Fillipe Romero

#include "PFFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPFFunctionLibrary::PlayBlockInteractFX(const UObject* WorldContextObject, USoundBase* SoundEffect, UNiagaraSystem* BlockEffect, UParticleSystem* ParticleEffect, FVector EffectLocation)
{
	UGameplayStatics::PlaySound2D(WorldContextObject, SoundEffect);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContextObject, BlockEffect, EffectLocation);
	UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject, ParticleEffect, EffectLocation);
}
