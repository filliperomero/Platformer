// Copyright Fillipe Romero

#include "Obstacles/PFFireBar.h"

#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

APFFireBar::APFFireBar()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	FireBars = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FireBars"));
	FireBars->SetupAttachment(RootComponent);
	FireBars->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovementComponent->RotationRate = FRotator(50.f, 0.f, 0.f);
}

void APFFireBar::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxOverlap);
}

void APFFireBar::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FireBars->ClearInstances();

	for (int32 Index = 0; Index < FireBarAmount; Index++)
	{
		const FVector InstanceLocation = FVector(0.f, 0.f, Index * FireBarDistanceApart);
		const FTransform& InstanceTransform = FTransform(FRotator(), InstanceLocation, FireBallSize);
		
		FireBars->AddInstance(InstanceTransform);
	}

	const float ZValue = FMath::Clamp(FireBarAmount - 1, 0, FireBarAmount - 1) * FireBarDistanceApart / 2;
	
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, ZValue));
	BoxCollision->SetBoxExtent(FVector(10.f, 50.f, ZValue));
	
	RotatingMovementComponent->RotationRate = RotationRate;
}

void APFFireBar::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || !bCanHit) return;

	bCanHit = false;

	// Modify this to use a function from the PlayerInterface
	const ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (IsValid(Character))
	{
		Character->GetMovementComponent()->Velocity = PlayerHitVelocity;
	}

	IPlayerInterface::Execute_AddHitPoints(OtherActor, HitPointsAmount);

	GetWorldTimerManager().SetTimer(CooldownTimer, this, &ThisClass::CooldownFinished, HitCooldown);
}

void APFFireBar::CooldownFinished()
{
	bCanHit = true;
}
