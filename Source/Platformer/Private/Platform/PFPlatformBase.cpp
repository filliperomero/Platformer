// Copyright Fillipe Romero

#include "Platform/PFPlatformBase.h"

#include "Components/BoxComponent.h"

APFPlatformBase::APFPlatformBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	SetRootComponent(Platform);

	CollisionTop = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionTop"));
	CollisionTop->SetupAttachment(RootComponent);
	CollisionTop->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionTop->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CollisionBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBottom"));
	CollisionBottom->SetupAttachment(RootComponent);
	CollisionBottom->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBottom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APFPlatformBase::BeginPlay()
{
	Super::BeginPlay();
}
