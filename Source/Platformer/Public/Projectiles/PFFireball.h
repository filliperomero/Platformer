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

	UFUNCTION()
	void OnProjectileMovementBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UStaticMeshComponent> Fireball;

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UParticleSystemComponent> FireballParticleSystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<UParticleSystem> ParticleEffect;

	UPROPERTY(EditAnywhere, Category = "Fireball Properties")
	TObjectPtr<USoundBase> SoundEffect;

private:
	int32 BouncesCounter = 0;
};
