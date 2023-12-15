// Copyright Fillipe Romero

#include "Game/PFGameMode.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"

APFGameMode::APFGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APFGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartingTime = GetWorld()->GetTimeSeconds();
}

void APFGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LevelTime > 0.f && !bStopLevelTime)
	{
		const float TimeLeft = InitialLevelTime - GetWorld()->GetTimeSeconds() + StartingTime;

		const uint32 SecondsLeft = FMath::CeilToInt(TimeLeft);

		if (CountdownInt != SecondsLeft)
		{
			LevelTime = FMath::CeilToInt(TimeLeft);
			OnLevelTimeChangedDelegate.Broadcast(LevelTime);
		}
		
		CountdownInt = SecondsLeft;
	}
}

void APFGameMode::RequestRespawn(ACharacter* Character, AController* Controller)
{
	Character->Destroy();

	RestartPlayerAtTransform(Controller, SpawnTransform);

	OnRequestPlayerRespawnDelegate.Broadcast(Controller);
}

void APFGameMode::SetLevelTime(const float InLevelTime)
{
	LevelTime = FMath::CeilToInt(InLevelTime);
	InitialLevelTime = InLevelTime;
	OnLevelTimeChangedDelegate.Broadcast(LevelTime);
}

void APFGameMode::CompleteLevel()
{
	bStopLevelTime = true;
	OnCompleteLevelDelegate.Broadcast();
}
