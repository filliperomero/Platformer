// Copyright Fillipe Romero

#include "Actors/PFClouds.h"

#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

APFClouds::APFClouds()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	Clouds = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Clouds"));
	Clouds->SetupAttachment(RootComponent);
	Clouds->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	Clouds->SetCastShadow(false);
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(RootComponent);
	SpawnArea->SetBoxExtent(FVector(5000.f, 1000.f, 2000.f));
}

void APFClouds::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	Clouds->ClearInstances();

	for (int32 Index = 0; Index < AmountOfClouds; Index++)
	{
		FVector InstanceLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetRelativeLocation(), SpawnArea->GetUnscaledBoxExtent());
		const float CloudScale = FMath::RandRange(CloudMinScale, CloudMaxScale);
		const FTransform& InstanceTransform = FTransform(FRotator(), InstanceLocation, FVector(CloudScale));
		
		Clouds->AddInstance(InstanceTransform);
	}
}
