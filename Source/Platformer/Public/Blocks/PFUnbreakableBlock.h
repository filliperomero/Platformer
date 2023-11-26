// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFBlockBase.h"
#include "PFUnbreakableBlock.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMER_API APFUnbreakableBlock : public APFBlockBase
{
	GENERATED_BODY()

public:
	APFUnbreakableBlock();

protected:
	virtual void BeginPlay() override;
	virtual void HitBlock(AActor* TargetActor) override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION(BlueprintImplementableEvent)
	void AnimateBlock();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TSubclassOf<AActor> CoinToSpawn;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<USoundBase> NotAbleToInteractSound;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	int32 MaxAmountOfInteract = 1;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	bool IsInvisible = false;

private:
	int32 AmountOfInteract = 0;
};
