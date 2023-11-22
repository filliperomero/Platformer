// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFBlockBase.generated.h"

class UNiagaraSystem;

UCLASS()
class PLATFORMER_API APFBlockBase : public AActor
{
	GENERATED_BODY()

public:
	APFBlockBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void HitBlock();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BlockMesh;

	bool bIsFinishedInteracting = false;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	int32 AmountOfCoins = 1;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	int32 AmountOfPoints = 10;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<UNiagaraSystem> InteractEffect;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<UParticleSystem> InteractParticleEffect;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<USoundBase> SoundEffect;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<UMaterial> InteractMaterial;
};
