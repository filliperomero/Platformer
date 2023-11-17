// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PlayerInterface.h"
#include "Logging/LogMacros.h"
#include "PFCharacter.generated.h"

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

	/** Player Interface */
	virtual void UpdateOverlappingPlatform_Implementation(APFPlatformBase* Platform) override;
	/** Player Interface */

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void Move(const FInputActionValue& Value);
	void PlayerDown(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

private:
	UPROPERTY()
	APFPlatformBase* OverlappingPlatform;
	
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

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

