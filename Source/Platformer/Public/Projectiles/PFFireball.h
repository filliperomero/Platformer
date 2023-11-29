// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFFireball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PLATFORMER_API APFFireball : public AActor
{
	GENERATED_BODY()

public:
	APFFireball();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UStaticMeshComponent> Fireball;

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UParticleSystemComponent> FireballParticleSystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
