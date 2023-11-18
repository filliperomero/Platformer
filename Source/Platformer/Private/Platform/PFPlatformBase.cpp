// Copyright Fillipe Romero

#include "Platform/PFPlatformBase.h"

#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"

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

	CollisionBottom->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionBottomBeginOverlap);
	CollisionBottom->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCollisionBottomEndOverlap);
}

void APFPlatformBase::OnCollisionBottomBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	Platform->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APFPlatformBase::OnCollisionBottomEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	Platform->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
