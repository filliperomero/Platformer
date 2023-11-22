// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlockInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UBlockInterface : public UInterface
{
	GENERATED_BODY()
};

class PLATFORMER_API IBlockInterface
{
	GENERATED_BODY()

public:
	// HitBlock ???
};
