// Copyright Fillipe Romero

#include "Actors/PFGoalPole.h"
#include "Character/PFCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/PFGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

APFGoalPole::APFGoalPole()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(32.f, 200.f, 1000.f));
	BoxCollision->SetRelativeLocation(FVector(32.f, 0.f, 1000.f));
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	FireworksAreaCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FireworksAreaCollision"));
	FireworksAreaCollision->SetupAttachment(RootComponent);
	FireworksAreaCollision->SetRelativeLocation(FVector(850.f, 0.f, 700.f));
	FireworksAreaCollision->SetBoxExtent(FVector(500.f, 200.f, 300.f));
	FireworksAreaCollision->SetLineThickness(5.f);
	FireworksAreaCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Flag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag"));
	Flag->SetupAttachment(RootComponent);
	Flag->SetRelativeScale3D(FVector(1.5f, 1.f, 1.f));
	Flag->SetRelativeLocation(FVector(85.f, 0.f, 845.f));
	Flag->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	
	FlagPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagPole"));
	FlagPole->SetupAttachment(RootComponent);
	FlagPole->SetRelativeScale3D(FVector(0.2f, 0.2f, 8.f));
	FlagPole->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	FlagPole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FlagBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagBase"));
	FlagBase->SetupAttachment(RootComponent);
	FlagBase->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	
	FlagTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagTop"));
	FlagTop->SetupAttachment(RootComponent);
	FlagTop->SetRelativeLocation(FVector(0.f, 0.f, 895.f));
	FlagTop->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	FlagTop->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FlagEndPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("FlagEndPoint"));
	FlagEndPoint->SetupAttachment(RootComponent);
	FlagEndPoint->SetRelativeLocation(FVector(85.f, 0.f, 150.f));
	FlagEndPoint->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	PlayerStartPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerStartPoint"));
	PlayerStartPoint->SetupAttachment(RootComponent);
	PlayerStartPoint->SetRelativeLocation(FVector(-25.f, 30.f, 850.f));

	PlayerEndPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerEndPoint"));
	PlayerEndPoint->SetupAttachment(RootComponent);
	PlayerEndPoint->SetRelativeLocation(FVector(-25.f, 30.f, 190.f));

	PlayerExplodePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerExplodePoint"));
	PlayerExplodePoint->SetupAttachment(RootComponent);
	PlayerExplodePoint->SetRelativeLocation(FVector(850.f, 0.f, 500.f));
}

void APFGoalPole::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxCollisionBeginOverlap);
}

void APFGoalPole::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || bReached) return;

	APFCharacter* Character = Cast<APFCharacter>(OtherActor);

	if (Character == nullptr) return;

	if (APFGameMode* GameMode = Cast<APFGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->CompleteLevel();
	}

	bReached = true;
	
	const FVector FlagAttachPointLocation = Character->GetFlagAttachPoint()->GetComponentLocation();
	const FVector FlagLocation = Flag->GetComponentLocation();
	
	if (FlagAttachPointLocation.Z > FlagLocation.Z)
	{
		Character->GetCapsuleComponent()->SetWorldLocation(PlayerStartPoint->GetComponentLocation());
	}
	else
	{
		Flag->SetWorldLocation(FVector(FlagLocation.X, FlagLocation.Y, FlagAttachPointLocation.Z));
	}

	Character->GetCapsuleComponent()->SetWorldRotation(FRotator(PlayerEndPoint->GetComponentRotation()));
	Character->GetCapsuleComponent()->AddLocalOffset(FVector(0.f, 30.f, 0.f));
	
	Character->GetCharacterMovement()->GravityScale = 0.f;
	Character->GetCharacterMovement()->Deactivate();

	if (Character->GetGoalPoleSequence())
	{
		Character->GetMesh()->PlayAnimation(Character->GetGoalPoleSequence(), false);
		Character->GetMesh()->SetPosition(1.9f);
	}

	RunGoalPoleLogic(Character);
}
