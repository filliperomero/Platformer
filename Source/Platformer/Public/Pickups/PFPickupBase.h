// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFPickupBase.generated.h"

class URotatingMovementComponent;
class USphereComponent;

UCLASS()
class PLATFORMER_API APFPickupBase : public AActor
{
	GENERATED_BODY()

public:
	APFPickupBase();
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> OverlapSphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> PickupMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, Category = "Pickup Properties")
	TObjectPtr<UParticleSystem> PickupEffect;	
};
