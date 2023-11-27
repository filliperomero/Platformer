// Copyright Fillipe Romero


#include "Blocks/PFPowerUpBlock.h"
#include "PFFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

APFPowerUpBlock::APFPowerUpBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	PowerUpCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerUpCollision"));
	PowerUpCollision->SetupAttachment(BlockMesh);
	PowerUpCollision->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	PowerUpCollision->SetLineThickness(5.f);

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
	PowerUpMesh->SetupAttachment(PowerUpCollision);
	PowerUpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PowerUpMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
}

void APFPowerUpBlock::BeginPlay()
{
	Super::BeginPlay();

	PowerUpCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPowerUpBoxBeginOverlap);
}

void APFPowerUpBlock::HitBlock(AActor* TargetActor)
{
	Super::HitBlock(TargetActor);

	if (!CanInteract)
	{
		if (NotAbleToInteractSound) UGameplayStatics::PlaySound2D(this, NotAbleToInteractSound);

		return;
	}

	FVector Location = GetActorLocation();
	Location.Z += 50;
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, Location);
	
	AnimateBlock();
	AnimatePowerUp();

	if (PowerUpEffect)
	{
		SpawnedParticle = UGameplayStatics::SpawnEmitterAtLocation(this, PowerUpEffect, Location);
	}

	if (InteractMaterial)
	{
		BlockMesh->SetMaterial(0, InteractMaterial);
	}

	CanInteract = false;
}

void APFPowerUpBlock::OnPowerUpBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	ShowFloatingPoints(OtherActor);
	IPlayerInterface::Execute_AddToPoints(OtherActor, AmountOfPoints);

	if (SpawnedParticle) SpawnedParticle->DestroyComponent();
	PowerUpMesh->DestroyComponent();
	PowerUpCollision->DestroyComponent();
}
