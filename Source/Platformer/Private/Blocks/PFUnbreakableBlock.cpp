// Copyright Fillipe Romero

#include "Blocks/PFUnbreakableBlock.h"
#include "PFFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

APFUnbreakableBlock::APFUnbreakableBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(BlockMesh);
	BoxCollision->SetBoxExtent(FVector(100.f, 50.f, 100.f));
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 51.f));
}

void APFUnbreakableBlock::BeginPlay()
{
	Super::BeginPlay();

	if (IsInvisible)
	{
		BlockMesh->SetVisibility(false);
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnBoxEndOverlap);
	}
	else
	{
		BoxCollision->Deactivate();
	}
}

void APFUnbreakableBlock::HitBlock(AActor* TargetActor)
{
	Super::HitBlock(TargetActor);
	
	if (AmountOfInteract >= MaxAmountOfInteract)
	{
		if (NotAbleToInteractSound) UGameplayStatics::PlaySound2D(this, NotAbleToInteractSound);

		return;
	}

	if (IsInvisible && !BlockMesh->IsVisible())
	{
		BlockMesh->SetVisibility(true);
		if (BoxCollision) BoxCollision->DestroyComponent();
	}

	const bool IsLastInteract = AmountOfInteract + 1 >= MaxAmountOfInteract;
	
	FVector Location = GetActorLocation();
	Location.Z += 50;
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, Location);
	
	if (InteractMaterial && IsLastInteract)
		BlockMesh->SetMaterial(0, InteractMaterial);
	
	ShowFloatingPoints(TargetActor);

	IPlayerInterface::Execute_AddToPoints(TargetActor, AmountOfPoints);
	IPlayerInterface::Execute_AddToCoins(TargetActor, AmountOfCoins);

	// For Future: Change this for an Niagara System
	if (CoinToSpawn)
		GetWorld()->SpawnActor<AActor>(CoinToSpawn, GetActorTransform());

	AnimateBlock();
	
	AmountOfInteract++;
}

void APFUnbreakableBlock::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	BlockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APFUnbreakableBlock::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	BlockMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
