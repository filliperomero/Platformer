// Copyright Fillipe Romero

#include "Enemies/PFGoomba.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/PlayerInterface.h"
#include "Platformer/Platformer.h"

APFGoomba::APFGoomba()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(55.f);
	GetCapsuleComponent()->SetCapsuleRadius(45.f);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	PlayerDetectRange = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectRange"));
	PlayerDetectRange->SetupAttachment(RootComponent);
	PlayerDetectRange->SetSphereRadius(2000.f);
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(55.f);
	SphereCollider->SetCollisionResponseToAllChannels(ECR_Block);
	SphereCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SphereCollider);
	PaperFlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StompBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("StompBoxCollider"));
	StompBoxCollider->SetupAttachment(SphereCollider);
	StompBoxCollider->SetBoxExtent(FVector(40.f, 100.f, 3.f));
	StompBoxCollider->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	StompBoxCollider->SetLineThickness(3.f);
	StompBoxCollider->SetCollisionResponseToAllChannels(ECR_Block);
	StompBoxCollider->SetCollisionResponseToChannel(ECC_Fireball, ECR_Ignore);
}

void APFGoomba::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereColliderBeginOverlap);
}

void APFGoomba::OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	IPlayerInterface::Execute_AddHitPoints(OtherActor, -Damage);
}
