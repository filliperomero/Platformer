// Copyright Fillipe Romero

#include "Platform/PFPlatformBase.h"

#include "Components/BoxComponent.h"

APFPlatformBase::APFPlatformBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(RootComponent);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	CollisionTop = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionTop"));
	CollisionTop->SetupAttachment(Platform);
	CollisionTop->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionTop->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CollisionBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBottom"));
	CollisionBottom->SetupAttachment(Platform);
	CollisionBottom->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBottom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APFPlatformBase::BeginPlay()
{
	Super::BeginPlay();
}
