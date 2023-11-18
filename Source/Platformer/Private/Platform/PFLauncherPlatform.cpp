// Copyright Fillipe Romero

#include "Platform/PFLauncherPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Interface/PlayerInterface.h"

APFLauncherPlatform::APFLauncherPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(RootComponent);

	MushroomTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MushroomTop"));
	MushroomTop->SetupAttachment(RootComponent);

	CollisionBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBottom"));
	CollisionBottom->SetupAttachment(MushroomTop);
	CollisionBottom->SetBoxExtent(FVector(50.f, 50.f, 60.f));
	CollisionBottom->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBottom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	MushroomTrunk = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("MushroomTrunk"));
	MushroomTrunk->SetupAttachment(RootComponent);
}

void APFLauncherPlatform::BeginPlay()
{
	Super::BeginPlay();

	CollisionBottom->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxBottomBeginOverlap);
	CollisionBottom->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnBoxBottomEndOverlap);
}

void APFLauncherPlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const FVector NewScale = FVector(MushroomTopScaleXY, MushroomTopScaleXY, MushroomTopScaleZ);
	MushroomTop->SetWorldScale3D(NewScale);

	const int32 AmountOfTrunks = FMath::TruncToInt32(TrunkEndPoint.Length() / 100.f);
	const int32 CurrentAmountOfTrunks = MushroomTrunk->GetInstanceCount();
	
	if (AmountOfTrunks < CurrentAmountOfTrunks)
	{
		// remove excess instances
		MushroomTrunk->ClearInstances();
	}

	for (int32 Index = 0; Index < AmountOfTrunks; Index++)
	{
		const FVector Location = FVector(0.f, 0.f, Index * -100.f);
		const FTransform& InstanceTransform = FTransform(FRotator(), Location, FVector(1.f, 1.f,1.f));
		
		MushroomTrunk->AddInstance(InstanceTransform);
	}
}

void APFLauncherPlatform::OnBoxBottomBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	MushroomTop->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APFLauncherPlatform::OnBoxBottomEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	MushroomTop->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
