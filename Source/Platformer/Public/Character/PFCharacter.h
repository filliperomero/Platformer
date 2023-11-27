// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PlayerInterface.h"
#include "Logging/LogMacros.h"
#include "PFCharacter.generated.h"

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
	virtual void UpdateOverlappingPlatform_Implementation(APFPlatformBase* Platform) override;
	virtual void AddToCoins_Implementation(int32 InCoins) override;
	virtual void AddHitPoints_Implementation(int32 InHitPoints) override;
	virtual void AddToPoints_Implementation(int32 InPoints) override;
	virtual void ActivatePowerUp_Implementation(const EPowerUpType PowerUpType) override;
	/** Player Interface */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void Move(const FInputActionValue& Value);
	void PlayerDown(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void HandleCharacterGrowth();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleDamageCharacter();

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

	UPROPERTY(VisibleAnywhere)
	int32 HitPoints { 2 };

private:
	UPROPERTY()
	TObjectPtr<APFPlatformBase> OverlappingPlatform;

	UPROPERTY()
	APFPlayerController* PFPlayerController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlayerDownAction;

	// For Now we are going to have this variable
	bool HasFlowerPower = false;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

