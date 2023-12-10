// Copyright Fillipe Romero

#include "Obstacles/PFInstaDeath.h"
#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"

APFInstaDeath::APFInstaDeath()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetBoxExtent(FVector(400.f, 400.f, 50.f));
	BoxCollision->SetLineThickness(3.f);
}

void APFInstaDeath::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxCollisionBeginOverlap);
}

void APFInstaDeath::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	IPlayerInterface::Execute_AddHitPoints(OtherActor, -99999);
}
