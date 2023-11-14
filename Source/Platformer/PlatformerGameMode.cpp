// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerGameMode.h"
#include "PlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformerGameMode::APlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
