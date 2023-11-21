// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PFFunctionLibrary.generated.h"

UCLASS()
class PLATFORMER_API UPFFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PFFunctionLibrary|Block")
	static void PlayBlockInteractFX(const UObject* WorldContextObject, USoundBase* SoundEffect, UNiagaraSystem* BlockEffect, UParticleSystem* ParticleEffect, FVector EffectLocation);
};
