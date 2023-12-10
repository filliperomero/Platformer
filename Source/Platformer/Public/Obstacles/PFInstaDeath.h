// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFInstaDeath.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFInstaDeath : public AActor
{
	GENERATED_BODY()

public:
	APFInstaDeath();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;
};
