﻿// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PFGoomba.generated.h"

class UPFPointsTextComponent;
class UBoxComponent;
class UPaperFlipbookComponent;
class USphereComponent;

UCLASS()
class PLATFORMER_API APFGoomba : public ACharacter
{
	GENERATED_BODY()

public:
	APFGoomba();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Die();

	UFUNCTION()
	virtual void OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerDetectRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPlayerDetectRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnSphereColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnStompBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> PlayerDetectRange;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> StompBoxCollider;

	UPROPERTY(EditAnywhere, Category = "Combat")
	int32 Damage = 1;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	int32 AmountOfPoints = 200;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	TObjectPtr<USoundBase> StompSound;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	TObjectPtr<UParticleSystem> DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	TSubclassOf<UPFPointsTextComponent> PointsTextComponentClass;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	bool bShouldMoveLeft = true;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	bool bIsSeeker = false;

private:
	void ShowFloatingPoints();
	void DieTimerFinished();

	FTimerHandle DieTimer;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	
	bool bIsPlayerInRange = false;
};
