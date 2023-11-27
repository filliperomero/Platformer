// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFBlockBase.h"
#include "PFPowerUpBlock.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFPowerUpBlock : public APFBlockBase
{
	GENERATED_BODY()

public:
	APFPowerUpBlock();

protected:
	virtual void BeginPlay() override;
	virtual void HitBlock(AActor* TargetActor) override;

	UFUNCTION()
	virtual void OnPowerUpBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent)
	void AnimateBlock();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimatePowerUp();
	
	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<USoundBase> NotAbleToInteractSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PowerUpMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> PowerUpCollision;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<UParticleSystem> PowerUpEffect;

private:
	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> SpawnedParticle;
	
	bool CanInteract = true;
};
