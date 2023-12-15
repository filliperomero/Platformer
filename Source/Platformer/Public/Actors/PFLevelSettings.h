// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFLevelSettings.generated.h"

UCLASS()
class PLATFORMER_API APFLevelSettings : public AActor
{
	GENERATED_BODY()

public:
	APFLevelSettings();
	void ToggleAudio(const bool bPauseAudio) const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTimeRunningOutWarningAudioComplete();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TObjectPtr<UAudioComponent> LevelMusicComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TObjectPtr<UAudioComponent> TimeRunningOutWarningAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TObjectPtr<UAudioComponent> TimeExpiredAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	TObjectPtr<UAudioComponent> LevelCompleteAudioComponent;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	int32 TimeLimitMax = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Settings")
	int32 TimeRunningOutWarning = 50;

private:
	bool bLevelComplete = false;
};
