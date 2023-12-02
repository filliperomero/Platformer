// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PFGoomba.generated.h"

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

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> PlayerDetectRange;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> StompBoxCollider;
	
};
