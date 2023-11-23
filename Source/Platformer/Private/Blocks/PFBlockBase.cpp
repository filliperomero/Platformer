// Copyright Fillipe Romero

#include "Blocks/PFBlockBase.h"

#include "Interface/PlayerInterface.h"
#include "UI/Widget/PFPointsTextComponent.h"

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
