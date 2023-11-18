// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFLauncherPlatform.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFLauncherPlatform : public AActor
{
	GENERATED_BODY()

public:
	APFLauncherPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MushroomTop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> CollisionBottom;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> MushroomTrunk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform Properties")
	float MushroomTopScaleXY = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform Properties")
	float MushroomTopScaleZ = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform Properties")
	FVector LaunchVelocity = FVector(0.f, 0.f, 2500.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform Properties", meta=(MakeEditWidget = true))
	FVector TrunkEndPoint = FVector(0.f, 0.f, 0.f);

	UFUNCTION()
	void OnBoxBottomBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxBottomEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	

public:
};
