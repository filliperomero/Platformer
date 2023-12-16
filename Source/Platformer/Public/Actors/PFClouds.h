// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFClouds.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFClouds : public AActor
{
	GENERATED_BODY()

public:
	APFClouds();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> SpawnArea;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> Clouds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clouds Properties")
	int32 AmountOfClouds = 25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clouds Properties")
	float CloudMinScale = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Clouds Properties")
	float CloudMaxScale = 10;
};
