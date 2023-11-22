// Copyright Fillipe Romero

#include "Blocks/PFBlockBase.h"

#include "Interface/PlayerInterface.h"

APFBlockBase::APFBlockBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);
}

void APFBlockBase::BeginPlay()
{
	Super::BeginPlay();

	BlockMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnMeshHit);
}

void APFBlockBase::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->Implements<UPlayerInterface>() || Hit.ImpactNormal.Z != 1) return;

	HitBlock();
}

void APFBlockBase::HitBlock()
{
}
