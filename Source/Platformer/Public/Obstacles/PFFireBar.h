// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFFireBar.generated.h"

class URotatingMovementComponent;
class UBoxComponent;

UCLASS()
class PLATFORMER_API APFFireBar : public AActor
{
	GENERATED_BODY()

public:
	APFFireBar();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual void OnBoxOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> FireBars;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	int32 FireBarAmount { 5 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	int32 FireBarDistanceApart { 60 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	FVector FireBallSize = FVector(0.5f, 0.5f, 0.5f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	FRotator RotationRate = FRotator(50.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	int32 HitPointsAmount { -1 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	FVector PlayerHitVelocity = FVector(0.f, 0.f, 500.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FireBar Properties")
	float HitCooldown { 1.f };

private:
	UPROPERTY()
	bool bCanHit { true };
	
	void CooldownFinished();

	FTimerHandle CooldownTimer;
	
};
