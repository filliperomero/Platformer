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

	UFUNCTION()
	void InteractTimerFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimateBlock();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TSubclassOf<AActor> CoinToSpawn;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	TObjectPtr<USoundBase> NotAbleToInteractSound;
	
	/** Amount of Time a Block can be interacted. Set to 0.f to make it interacted only once */
	UPROPERTY(EditAnywhere, Category = "Block Properties")
	float InteractTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Block Properties")
	bool IsInvisible = false;

private:
	bool CanInteract = true;
	bool IsFirstInteract = true;
	bool IsLastInteract = false;

	UPROPERTY()
	FTimerHandle InteractTimer;
};
