// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PlayerInterface.h"
#include "Logging/LogMacros.h"
#include "PFCharacter.generated.h"

class APFFireball;
class APFPlayerController;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APFCharacter : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	APFCharacter();
	virtual void PossessedBy(AController* NewController) override;

	/** Player Interface */
	virtual void UpdateOverlappingActor_Implementation(AActor* InOverlappingActor) override;
	virtual void AddToCoins_Implementation(int32 InCoins) override;
	virtual void AddHitPoints_Implementation(int32 InHitPoints) override;
	virtual void AddLives_Implementation(int32 InLives) override;
	virtual void AddToPoints_Implementation(int32 InPoints) override;
	virtual void ActivatePowerUp_Implementation(const EPowerUpType PowerUpType) override;
	virtual bool CanBreakBlock_Implementation() override;
	virtual void LaunchCharacter_Implementation(const FVector& LaunchVelocity) override;
	virtual void PlayForceFeedback_Implementation(UForceFeedbackEffect* ForceFeedbackEffect) override;
	/** Player Interface */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void Move(const FInputActionValue& Value);
	void PlayerDown(const FInputActionValue& Value);
	void PlayerUp(const FInputActionValue& Value);
	void ShootFireball(const FInputActionValue& Value);
	void PauseGame(const FInputActionValue& Value);
	void SprintStarted(const FInputActionValue& Value);
	void SprintCompleted(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void HandleCharacterGrowth();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleDamageCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimateCharacterDeath();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	bool bCanAdjustCameraInRealtime = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	float CameraDistanceFromPlayer = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	float CameraXOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	float CameraYOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	float CameraZOffset = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Realtime Camera Settings (Temporary)")
	float CameraLagSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> DamagedMaterial_0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> DamagedMaterial_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> DamagedMaterial_2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> PowerUpSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> PowerDownSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> PauseMenuSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UParticleSystem> DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> DeathSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> GoalPoleSequence;

	UPROPERTY(VisibleAnywhere)
	int32 HitPoints { 1 };

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<APFFireball> FireballClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USoundBase> FireballSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireballDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float DeathDelay = 2.5f;

private:
	UPROPERTY()
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY()
	APFPlayerController* PFPlayerController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> FlagAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlayerDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlayerUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	// For Now we are going to have this variable
	bool bHasFlowerPower = false;
	bool bCanShoot = true;

	FTimerHandle FireballTimer;
	FTimerHandle DeathTimer;

	void Die();
	void FireballTimerFinished();
	void DeathTimerFinished();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UArrowComponent* GetFlagAttachPoint() const { return FlagAttachPoint; }
	FORCEINLINE UAnimSequence* GetGoalPoleSequence() const { return GoalPoleSequence; }
};

