// Copyright Fillipe Romero

#include "Actors/PFLevelSettings.h"
#include "Components/AudioComponent.h"
#include "Game/PFGameMode.h"
#include "Kismet/GameplayStatics.h"

APFLevelSettings::APFLevelSettings()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	LevelMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LevelMusicComponent"));
	LevelMusicComponent->SetupAttachment(RootComponent);
	LevelMusicComponent->SetAutoActivate(false);
	
	TimeRunningOutWarningAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TimeRunningOutWarningAudioComponent"));
	TimeRunningOutWarningAudioComponent->SetupAttachment(RootComponent);
	TimeRunningOutWarningAudioComponent->SetAutoActivate(false);
	
	TimeExpiredAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("TimeExpiredAudioComponent"));
	TimeExpiredAudioComponent->SetupAttachment(RootComponent);
	TimeExpiredAudioComponent->SetAutoActivate(false);
	
	LevelCompleteAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LevelCompleteAudioComponent"));
	LevelCompleteAudioComponent->SetupAttachment(RootComponent);
	LevelCompleteAudioComponent->SetAutoActivate(false);
}

void APFLevelSettings::ToggleAudio(const bool bPauseAudio) const
{
	if (!bLevelComplete)
	{
		LevelMusicComponent->SetPaused(bPauseAudio);
	}
}

void APFLevelSettings::BeginPlay()
{
	Super::BeginPlay();

	TimeRunningOutWarningAudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::OnTimeRunningOutWarningAudioComplete);

	if (APFGameMode* GameMode = Cast<APFGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnRequestPlayerRespawnDelegate.AddLambda(
		[this](AController* Controller)
			{
				LevelMusicComponent->SetPitchMultiplier(1.0);
			}
		);

		GameMode->SetLevelTime(TimeLimitMax);

		GameMode->OnCompleteLevelDelegate.AddLambda(
			[this]()
			{
				bLevelComplete = true;
				LevelMusicComponent->Stop();
				TimeRunningOutWarningAudioComponent->Stop();
				LevelCompleteAudioComponent->Play();

				GetWorldTimerManager().SetTimer(ChangeLevelTimer, this, &ThisClass::ChangeLevelTimerFinished, DelayToChangeLevel);
			}
		);

		GameMode->OnLevelTimeChangedDelegate.AddLambda(
		[this](int32 LevelTimeValue)
			{
				if (bLevelComplete) return;
			
				if (LevelTimeValue == TimeRunningOutWarning)
				{
					LevelMusicComponent->SetPaused(true);
					TimeRunningOutWarningAudioComponent->Play();
				}
				else if (LevelTimeValue <= 0)
				{
					LevelMusicComponent->Stop();
					TimeRunningOutWarningAudioComponent->Stop();
				}
			}
		);
	}

	LevelMusicComponent->Play();
}

void APFLevelSettings::OnTimeRunningOutWarningAudioComplete()
{
	if (LevelMusicComponent->bIsPaused && !bLevelComplete)
	{
		LevelMusicComponent->SetPaused(false);
		LevelMusicComponent->SetPitchMultiplier(1.05); 
	}
}

void APFLevelSettings::ChangeLevelTimerFinished() const
{
	UGameplayStatics::OpenLevel(this, NextLevelName);
}
