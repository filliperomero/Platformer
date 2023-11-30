// Copyright Fillipe Romero

#include "Projectiles/PFFireball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Platformer/Platformer.h"

APFFireball::APFFireball()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Fireball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fireball"));
	SetRootComponent(Fireball);
	Fireball->SetCollisionResponseToAllChannels(ECR_Block);
	Fireball->SetCollisionObjectType(ECC_Fireball);
	Fireball->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Fireball->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Fireball->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Fireball->SetCollisionResponseToChannel(ECC_Fireball, ECR_Ignore);

	FireballParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireballParticleSystemComponent"));
	FireballParticleSystemComponent->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = .5f;
	ProjectileMovement->Friction = 0.f;
}

void APFFireball::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(2.f);

	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ThisClass::OnProjectileMovementBounce);
}

void APFFireball::OnProjectileMovementBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (ImpactResult.Normal.GetAbs().Z >= 0.9)
	{
		++BouncesCounter;
	} 

	if (BouncesCounter >= 2 || ImpactResult.Normal.GetAbs().Z < 0.9)
	{
		if (ParticleEffect)
			UGameplayStatics::SpawnEmitterAtLocation(this, ParticleEffect, GetActorLocation());

		if (SoundEffect)
			UGameplayStatics::PlaySound2D(this, SoundEffect);

		Destroy();
	}
}
