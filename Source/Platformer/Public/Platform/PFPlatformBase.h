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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionTop;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionBottom;

public:
	UStaticMeshComponent* GetPlatformMesh() const { return Platform; }

};
