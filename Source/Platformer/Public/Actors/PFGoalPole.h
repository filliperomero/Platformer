// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFGoalPole.generated.h"

class APFCharacter;
class UArrowComponent;
class UBoxComponent;

UCLASS()
class PLATFORMER_API APFGoalPole : public AActor
{
	GENERATED_BODY()

public:
	APFGoalPole();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void RunGoalPoleLogic(APFCharacter* Character);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> FireworksAreaCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Flag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagPole;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FlagTop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBillboardComponent> FlagEndPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> PlayerStartPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> PlayerEndPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> PlayerExplodePoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	int32 FireworkPoints = 500;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	int32 FireworkShowSpecialNumber = 7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	TObjectPtr<USoundBase> SoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	TObjectPtr<UParticleSystem> CharacterExplosionParticleEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	TObjectPtr<USoundBase> CharacterExplosionSoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	TObjectPtr<USoundBase> FireworkSoundEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GoalPole Properties")
	TObjectPtr<UParticleSystem> FireworkParticleEffect;
	
private:
	bool bReached = false;
};
