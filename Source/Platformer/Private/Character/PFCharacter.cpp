// Copyright Fillipe Romero

#include "Character/PFCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Game/PFGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacles/PFWarpPipe.h"
#include "Platform/PFPlatformBase.h"
#include "Player/PFPlayerController.h"
#include "Projectiles/PFFireball.h"
#include "UI/HUD/PFHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APFCharacter::APFCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 2500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 1500.f;
	GetCharacterMovement()->GravityScale = 2.5f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
	GetCharacterMovement()->GroundFriction = 2.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1500.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.f;
	CameraBoom->bDoCollisionTest = false;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APFCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (APFPlayerController* PC = Cast<APFPlayerController>(GetController()))
	{
		if (APFHUD* PFHUD = Cast<APFHUD>(PC->GetHUD()))
		{
			PFHUD->InitOverlay(PC);
		}
	}
}

void APFCharacter::UpdateOverlappingActor_Implementation(AActor* InOverlappingActor)
{
  	OverlappingActor = InOverlappingActor;
}

void APFCharacter::AddToCoins_Implementation(int32 InCoins)
{
	PFPlayerController = PFPlayerController == nullptr ? GetController<APFPlayerController>() : PFPlayerController;
	check(PFPlayerController)
	
	return PFPlayerController->AddCoins(InCoins);
}

void APFCharacter::AddHitPoints_Implementation(int32 InHitPoints)
{
	HitPoints = FMath::Clamp(HitPoints + InHitPoints, 0, 2);

	if (HitPoints == 0)
	{
		Destroy();
		return;
	}

	switch (HitPoints)
	{
	case 0:
		GetMesh()->SetMaterial(0, DamagedMaterial_0);
		break;
	case 1:
		GetMesh()->SetMaterial(0, DamagedMaterial_1);
		break;
	case 2:
		GetMesh()->SetMaterial(0, DamagedMaterial_2);
		break;
	default:
		GetMesh()->SetMaterial(0, DamagedMaterial_1);
		break;
	}

	if (InHitPoints > 0)
	{
		if (PowerUpSound) UGameplayStatics::PlaySound2D(this, PowerUpSound);
	}
	else if (InHitPoints < 0 && HitPoints != 0)
	{
		if (PowerDownSound) UGameplayStatics::PlaySound2D(this, PowerDownSound);
		bHasFlowerPower = false;
		HandleDamageCharacter();
	}
}

void APFCharacter::AddToPoints_Implementation(int32 InPoints)
{
	PFPlayerController = PFPlayerController == nullptr ? GetController<APFPlayerController>() : PFPlayerController;
	check(PFPlayerController)
	
	return PFPlayerController->AddPoints(InPoints);
}

void APFCharacter::ActivatePowerUp_Implementation(const EPowerUpType PowerUpType)
{
	if (PowerUpType == EPowerUpType::EPT_FlowerPower)
	{
		if (PowerUpSound) UGameplayStatics::PlaySound2D(this, PowerUpSound);
		Execute_AddHitPoints(this, 1);
		HandleCharacterGrowth();
		bHasFlowerPower = true;
	}
}

bool APFCharacter::CanBreakBlock_Implementation()
{
	return HitPoints >= 2;
}

void APFCharacter::LaunchCharacter_Implementation(const FVector& LaunchVelocity)
{
	ACharacter::LaunchCharacter(LaunchVelocity, false, false);
}

void APFCharacter::PlayForceFeedback_Implementation(UForceFeedbackEffect* ForceFeedbackEffect)
{
	PFPlayerController = PFPlayerController == nullptr ? GetController<APFPlayerController>() : PFPlayerController;
	check(PFPlayerController)
	
	PFPlayerController->ClientPlayForceFeedback(ForceFeedbackEffect);
}

void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (APFGameMode* GameMode = Cast<APFGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->SetSpawnTransform(GetActorTransform());
	}
}

void APFCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCanAdjustCameraInRealtime)
	{
		CameraBoom->SetRelativeLocation(FVector(CameraXOffset, CameraYOffset, CameraZOffset));
		CameraBoom->CameraLagSpeed = CameraLagSpeed;
		CameraBoom->TargetArmLength = CameraDistanceFromPlayer;
	}
}

void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APFCharacter::Move);
		EnhancedInputComponent->BindAction(PlayerDownAction, ETriggerEvent::Started, this, &APFCharacter::PlayerDown);
		EnhancedInputComponent->BindAction(PlayerUpAction, ETriggerEvent::Started, this, &APFCharacter::PlayerUp);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APFCharacter::ShootFireball);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APFCharacter::FireballTimerFinished()
{
	bCanShoot = true;
}

void APFCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.X);
		// AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APFCharacter::PlayerDown(const FInputActionValue& Value)
{
	if (!IsValid(OverlappingActor)) return;

	if (const APFPlatformBase* PlatformBase = Cast<APFPlatformBase>(OverlappingActor))
	{
		PlatformBase->GetPlatformMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else if (APFWarpPipe* WarpPipe = Cast<APFWarpPipe>(OverlappingActor))
	{
		WarpPipe->Interact(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unrecognized Actor, PlayerDown Function couldn't run properly."))
	}

	OverlappingActor = nullptr;
}

void APFCharacter::PlayerUp(const FInputActionValue& Value)
{
	if (!IsValid(OverlappingActor)) return;
	
	if (APFWarpPipe* WarpPipe = Cast<APFWarpPipe>(OverlappingActor))
	{
		WarpPipe->Interact(this);
	}

	OverlappingActor = nullptr;
}

void APFCharacter::ShootFireball(const FInputActionValue& Value)
{
	if (!bHasFlowerPower || !bCanShoot) return;

	bCanShoot = false;

	GetWorldTimerManager().SetTimer(FireballTimer, this, &APFCharacter::FireballTimerFinished, FireballDelay);
	
	const FVector SocketLocation = GetMesh()->GetSocketLocation(HandSocketName);
	const float YawRotation = GetActorForwardVector().X < 0 ? 180.f : 0.f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(FRotator(-30.f, YawRotation, 0.f).Quaternion());
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	GetWorld()->SpawnActor<APFFireball>(FireballClass, SpawnTransform, SpawnParameters);
	
	if (FireballSound) UGameplayStatics::PlaySoundAtLocation(this, FireballSound, GetActorLocation());
}
