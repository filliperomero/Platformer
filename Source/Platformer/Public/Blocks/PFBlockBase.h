// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFBlockBase.generated.h"

class USphereComponent;
class UPFPointsTextComponent;
class UNiagaraSystem;

UCLASS()
class PLATFORMER_API APFBlockBase : public AActor
{
	GENERATED_BODY()

public:
	APFBlockBase();

	virtual void PBlockOn();
	virtual void PBlockOff();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void HitBlock(AActor* TargetActor);
	void ShowFloatingPoints(AActor* TargetActor);

	UFUNCTION()
	virtual void OnCoinColliderOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BlockMesh;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TSubclassOf<UPFPointsTextComponent> PointsTextComponentClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CoinCollider;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UChildActorComponent> ChildActorComponent;

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
