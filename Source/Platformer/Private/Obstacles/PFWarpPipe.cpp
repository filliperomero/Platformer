// Copyright Fillipe Romero

#include "Obstacles/PFWarpPipe.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

APFWarpPipe::APFWarpPipe()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	PipeTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PipeTop"));
	PipeTop->SetupAttachment(RootComponent);
	PipeTop->SetRelativeLocation(FVector(0.f, 0.f, 35.f));
	PipeTop->SetRelativeScale3D(FVector(2.75f, 2.75f, 0.5f));
	
	PipeBody = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PipeBody"));
	PipeBody->SetupAttachment(RootComponent);
	PipeBody->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	PipeBody->SetRelativeScale3D(FVector(2.25f, 2.25f, 1.f));
	
	PipeInside = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PipeInside"));
	PipeInside->SetupAttachment(PipeTop);
	PipeInside->SetRelativeLocation(FVector(0.f, 0.f, 25.5f));
	PipeInside->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.5f));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(PipeTop);
	CapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	CapsuleComponent->SetCapsuleHalfHeight(300.f);
	CapsuleComponent->SetCapsuleRadius(40.f);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WarpInPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("WarpInPoint"));
	WarpInPoint->SetupAttachment(RootComponent);
	WarpInPoint->SetRelativeLocation(FVector(0.f, 0.f, 70.f));

	WarpOutPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("WarpOutPoint"));
	WarpOutPoint->SetupAttachment(RootComponent);
	WarpOutPoint->SetRelativeLocation(FVector(0.f, 0.f, -35.f));
}

void APFWarpPipe::Interact(APFCharacter* Character)
{
	AnimateCharacter(Character);

	if (SoundEffect) UGameplayStatics::PlaySound2D(this, SoundEffect);
}

void APFWarpPipe::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCapsuleBeginOverlap);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCapsuleEndOverlap);
}

void APFWarpPipe::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	const int32 AmountOfPipes = FMath::TruncToInt32(PipeEndPoint.Length() / 100.f);
	
	if (AmountOfPipes < PipeBody->GetInstanceCount())
	{
		PipeBody->ClearInstances();
	}

	for (int32 Index = 0; Index < AmountOfPipes; Index++)
	{
		const FVector Location = FVector(0.f, 0.f, Index * -100.f);
		const FTransform& InstanceTransform = FTransform(FRotator(), Location, FVector(1.f, 1.f,1.f));
		
		PipeBody->AddInstance(InstanceTransform);
	}
}

void APFWarpPipe::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || !bCanInteract) return;
	
	IPlayerInterface::Execute_UpdateOverlappingActor(OtherActor, this);
}

void APFWarpPipe::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UPlayerInterface>() || !bCanInteract) return;

	IPlayerInterface::Execute_UpdateOverlappingActor(OtherActor, nullptr);
}
