// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFWarpPipe.generated.h"

class APFCharacter;
class UCapsuleComponent;

UCLASS()
class PLATFORMER_API APFWarpPipe : public AActor
{
	GENERATED_BODY()

public:
	APFWarpPipe();

	void Interact(APFCharacter* Character);

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void AnimateCharacter(APFCharacter* Character);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PipeTop;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PipeInside;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> PipeBody;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBillboardComponent> WarpInPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBillboardComponent> WarpOutPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Warp Pipe Properties")
	TObjectPtr<USoundBase> SoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Warp Pipe Properties", meta=(MakeEditWidget = true))
	FVector PipeEndPoint = FVector(0.f, 0.f, -100.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Warp Pipe Properties")
	FVector WarpToLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WarpPipe Properties")
	bool bIsPipeExitDown = false;

	UPROPERTY(EditAnywhere, Category = "WarpPipe Properties")
	bool bCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WarpPipe Properties")
	bool bIsPipeDown = true;
};
