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

	// Since we don't have InteractTime, it'll always be the last interact
	if (InteractTime <= 0.f) IsLastInteract = true;
}

// Refactor code to remove the MaxAmountOfInteract and use a Timer now since the Project uses it
void APFUnbreakableBlock::HitBlock(AActor* TargetActor)
{
	Super::HitBlock(TargetActor);

	if (IsFirstInteract && InteractTime > 0.f)
	{
		IsFirstInteract = false;
		GetWorldTimerManager().SetTimer(InteractTimer, this, &ThisClass::InteractTimerFinished, InteractTime);
	}

	if (!CanInteract)
	{
		if (NotAbleToInteractSound) UGameplayStatics::PlaySound2D(this, NotAbleToInteractSound);

		return;
	}

	if (IsInvisible && !BlockMesh->IsVisible())
	{
		BlockMesh->SetVisibility(true);
		if (BoxCollision) BoxCollision->DestroyComponent();
	}
	
	FVector Location = GetActorLocation();
	Location.Z += 50;
	
	UPFFunctionLibrary::PlayBlockInteractFX(this, SoundEffect, nullptr, InteractParticleEffect, Location);
	
	ShowFloatingPoints(TargetActor);

	IPlayerInterface::Execute_AddToPoints(TargetActor, AmountOfPoints);
	IPlayerInterface::Execute_AddToCoins(TargetActor, AmountOfCoins);

	// For Future: Change this for an Niagara System
	if (CoinToSpawn)
		GetWorld()->SpawnActor<AActor>(CoinToSpawn, GetActorTransform());

	AnimateBlock();

	if (InteractMaterial && IsLastInteract)
	{
		BlockMesh->SetMaterial(0, InteractMaterial);
		CanInteract = false;
	}
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

void APFUnbreakableBlock::InteractTimerFinished()
{
	IsLastInteract = true;
}
