// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFPBlock.generated.h"

class APFBlockBase;
class UBoxComponent;

UCLASS()
class PLATFORMER_API APFPBlock : public AActor
{
	GENERATED_BODY()

public:
	APFPBlock();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BlockMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> SmashedBlockBaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> SmashedBlockTopMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> SmashedBoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	TObjectPtr<USoundBase> SoundEffect;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	TObjectPtr<UParticleSystem> ParticleEffect;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	TObjectPtr<UForceFeedbackEffect> ForceFeedbackEffect;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	float TimeDuration = 8.f;

	UPROPERTY(EditAnywhere, Category = "P-Block Properties")
	FName Tag = FName("PBlock");

private:
	UPROPERTY()
	TArray<APFBlockBase*> BaseBlocks;

	void TimerFinished();

	FTimerHandle TimerHandle;
};
