// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFPlatformBase.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFPlatformBase : public AActor
{
	GENERATED_BODY()

public:
	APFPlatformBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Platform;

	UFUNCTION()
	void OnCollisionBottomBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBottomEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionTop;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionBottom;

public:
	UStaticMeshComponent* GetPlatformMesh() const { return Platform; }

};
