// Copyright Fillipe Romero

#include "Blocks/PFBlockBase.h"

#include "Components/SphereComponent.h"
#include "Interface/PlayerInterface.h"
#include "UI/Widget/PFPointsTextComponent.h"

APFBlockBase::APFBlockBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	ChildActorComponent->SetupAttachment(BlockMesh);
	ChildActorComponent->SetVisibility(false);
	ChildActorComponent->Deactivate();

	CoinCollider = CreateDefaultSubobject<USphereComponent>(TEXT("CoinCollider"));
	CoinCollider->SetupAttachment(ChildActorComponent);
	CoinCollider->SetSphereRadius(35.f);
}

void APFBlockBase::BeginPlay()
{
	Super::BeginPlay();

	BlockMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnMeshHit);
	
	if (ActorHasTag(FName("PBlock")))
	{
		CoinCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCoinColliderOverlap);
	}
	else
	{
		ChildActorComponent->DestroyComponent();
		CoinCollider->DestroyComponent();
	}
}

void APFBlockBase::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->Implements<UPlayerInterface>() || Hit.ImpactNormal.Z != 1) return;

	HitBlock(OtherActor);
}

void APFBlockBase::HitBlock(AActor* TargetActor)
{
}

void APFBlockBase::ShowFloatingPoints(AActor* TargetActor)
{
	// TODO: Still need to understand why this does not work with Actor class with this set of components
	if (PointsTextComponentClass == nullptr) return;

	UPFPointsTextComponent* PointsTextComponent = NewObject<UPFPointsTextComponent>(TargetActor, PointsTextComponentClass);
	PointsTextComponent->RegisterComponent();
	PointsTextComponent->AttachToComponent(TargetActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PointsTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	PointsTextComponent->SetPointsText(AmountOfPoints);
}

void APFBlockBase::OnCoinColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || !ChildActorComponent->IsVisible()) return;
	
	// Destroy block if P-Block coin inside is collected
	Destroy();
}

void APFBlockBase::PBlockOn()
{
	BlockMesh->SetVisibility(false);
	BlockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (ChildActorComponent) ChildActorComponent->SetVisibility(true);
}

void APFBlockBase::PBlockOff()
{
	BlockMesh->SetVisibility(true);
	BlockMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (ChildActorComponent) ChildActorComponent->SetVisibility(false);
}
