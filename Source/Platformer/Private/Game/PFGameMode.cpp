// Copyright Fillipe Romero

#include "Game/PFGameMode.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"

APFGameMode::APFGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APFGameMode::RequestRespawn(ACharacter* Character, AController* Controller)
{
	Character->Destroy();

	RestartPlayerAtTransform(Controller, SpawnTransform);
}
