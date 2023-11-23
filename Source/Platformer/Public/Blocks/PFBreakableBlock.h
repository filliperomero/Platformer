// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFBlockBase.h"
#include "PFBreakableBlock.generated.h"

UCLASS()
class PLATFORMER_API APFBreakableBlock : public APFBlockBase
{
	GENERATED_BODY()

public:
	APFBreakableBlock();

protected:
	virtual void BeginPlay() override;

	virtual void HitBlock(AActor* TargetActor) override;
};
