// Copyright Fillipe Romero

#include "Actors/PFCheckpoint.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Game/PFGameMode.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

class APFGameMode;

APFCheckpoint::APFCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(200.f, 200.f, 500.f));
	BoxCollision->SetLineThickness(5.f);
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	BoxCollision->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	
	FlagPivotPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPivotPoint"));
	FlagPivotPoint->SetupAttachment(BoxCollision);
	FlagPivotPoint->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	FlagPivotPoint->SetRelativeLocation(FVector(-200.f, 0.f, -400.f));
	
	FlagBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagBase"));
	FlagBase->SetupAttachment(BoxCollision);
	FlagBase->SetRelativeScale3D(FVector(0.5f, 2.f, 2.f));
	FlagBase->SetRelativeLocation(FVector(-200.f, 0.f, -500.f));
	
	FlagArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagArm"));
	FlagArm->SetupAttachment(BoxCollision);
	FlagArm->SetRelativeScale3D(FVector(0.5f, 1.f, 1.f));
	FlagArm->SetRelativeLocation(FVector(-205.f, 0.f, -390.f));
	FlagArm->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
	
	Flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	Flag->SetupAttachment(FlagArm);
	Flag->SetRelativeLocation(FVector(10.f, -10.f, 350.f));
	Flag->SetRelativeScale3D(FVector(0.2f, 1.f, 2.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
}

void APFCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxCollisionBeginOverlap);
}

void APFCheckpoint::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || bReached) return;

	bReached = true;

	if (APFGameMode* GameMode = Cast<APFGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->SetSpawnTransform(GetActorTransform());

		AnimateFlag();
		
		if (SoundEffect) UGameplayStatics::PlaySound2D(this, SoundEffect);
		
		if (CheckpointEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				CheckpointEffect,
				GetActorLocation() + FVector(0.f, 0.f, 200.f),
				FRotator(),
				FVector(10.f, 10.f, 10.f)
			);
		}
	}
}
