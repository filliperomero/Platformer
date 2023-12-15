// Copyright Fillipe Romero

#include "PFPBlock.h"
#include "Blocks/PFBlockBase.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/PFLevelSettings.h"
#include "Game/PFGameMode.h"

APFPBlock::APFPBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BlockMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BlockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BoxCollider->SetBoxExtent(FVector(42.f, 42.f, 50.f));
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);

	SmashedBlockBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmashedBlockBaseMesh"));
	SmashedBlockBaseMesh->SetupAttachment(RootComponent);
	SmashedBlockBaseMesh->SetRelativeLocation(FVector(0.f, 0.f, 7.85f));
	SmashedBlockBaseMesh->SetRelativeScale3D(FVector(0.92f, 0.92f, 0.15f));
	SmashedBlockBaseMesh->SetVisibility(false);

	SmashedBlockTopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmashedBlockTopMesh"));
	SmashedBlockTopMesh->SetupAttachment(RootComponent);
	SmashedBlockTopMesh->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	SmashedBlockTopMesh->SetRelativeScale3D(FVector(0.85f, 0.85f, 0.1f));
	SmashedBlockTopMesh->SetVisibility(false);

	SmashedBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SmashedBoxCollider"));
	SmashedBoxCollider->SetupAttachment(RootComponent);
	SmashedBoxCollider->SetBoxExtent(FVector(42.f, 100.f, 13.f));
	SmashedBoxCollider->SetCollisionResponseToAllChannels(ECR_Block);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);
}

void APFPBlock::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentHit.AddDynamic(this, &ThisClass::OnBoxColliderHit);
	
	if (APFGameMode* GameMode = Cast<APFGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnCompleteLevelDelegate.AddLambda(
			[this]()
			{
				AudioComponent->Stop();
			}
		);
	}
}

void APFPBlock::OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->Implements<UPlayerInterface>() || Hit.ImpactNormal.Z != -1) return;
	
	IPlayerInterface::Execute_LaunchCharacter(OtherActor, FVector(0.f, 0.f, 400.f));
	
	if (SoundEffect) UGameplayStatics::PlaySound2D(this, SoundEffect);

	const FVector Location = SmashedBlockBaseMesh->GetComponentLocation();

	if (ParticleEffect) UGameplayStatics::SpawnEmitterAtLocation(this, ParticleEffect, Location);

	AudioComponent->Play();
	if (IsValid(PFLevelSettings)) PFLevelSettings->ToggleAudio(true);

	if (CameraShake)
		UGameplayStatics::PlayWorldCameraShake(this, CameraShake, OtherActor->GetActorLocation(), 1000.f, 2000.f);
	
	if (ForceFeedbackEffect)
		IPlayerInterface::Execute_PlayForceFeedback(OtherActor, ForceFeedbackEffect);

	// Show Meshes and destroy components
	SmashedBlockTopMesh->SetVisibility(true);
	SmashedBlockBaseMesh->SetVisibility(true);
	BlockMesh->DestroyComponent();
	BoxCollider->DestroyComponent();

	TArray<AActor*> OutBlocks;
	UGameplayStatics::GetAllActorsWithTag(this, Tag, OutBlocks);

	for (AActor* Block : OutBlocks)
	{
		if (APFBlockBase* BaseBlock = Cast<APFBlockBase>(Block))
		{
			BaseBlock->PBlockOn();
			BaseBlocks.AddUnique(BaseBlock);
		}
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::TimerFinished, TimeDuration);
}

void APFPBlock::TimerFinished()
{
	for (APFBlockBase* Block : BaseBlocks)
	{
		if (IsValid(Block))
		{
			Block->PBlockOff();
		}
	}
	
	AudioComponent->Stop();
	
	if (IsValid(PFLevelSettings)) PFLevelSettings->ToggleAudio(false);
}
