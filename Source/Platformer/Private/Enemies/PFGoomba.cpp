// Copyright Fillipe Romero

#include "Enemies/PFGoomba.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer/Platformer.h"
#include "Projectiles/PFFireball.h"
#include "UI/Widget/PFPointsTextComponent.h"

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
	SphereCollider->OnComponentHit.AddDynamic(this, &ThisClass::OnSphereColliderHit);
	StompBoxCollider->OnComponentHit.AddDynamic(this, &ThisClass::OnStompBoxColliderHit);
}

void APFGoomba::Die()
{
	if (DeathSound) UGameplayStatics::PlaySound2D(this, DeathSound);
	
	if (DeathEffect)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, SphereCollider->GetComponentLocation());

	Destroy();
}

void APFGoomba::OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;

	IPlayerInterface::Execute_AddHitPoints(OtherActor, -Damage);
}

void APFGoomba::OnSphereColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const APFFireball* Fireball = Cast<APFFireball>(OtherActor);

	if (Fireball == nullptr) return;

	IPlayerInterface::Execute_AddToPoints(Fireball->GetOwner(), AmountOfPoints);

	Die();
}

void APFGoomba::OnStompBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->Implements<UPlayerInterface>() || Hit.ImpactNormal.Z != -1) return;

	SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	if (StompSound) UGameplayStatics::PlaySound2D(this, StompSound);
	
	IPlayerInterface::Execute_AddToPoints(OtherActor, AmountOfPoints);
	ShowFloatingPoints();

	PaperFlipbookComponent->SetWorldScale3D(FVector(.25f, .25f, .1f));
	PaperFlipbookComponent->AddWorldOffset(FVector(0.f, 0.f, -35.f));
	
	GetCharacterMovement()->DisableMovement();
	StompBoxCollider->DestroyComponent();

	GetWorldTimerManager().SetTimer(DieTimer, this, &ThisClass::DieTimerFinished, 0.5f);
}

// TODO: Refactor this function to be reusable across the application
void APFGoomba::ShowFloatingPoints()
{
	if (PointsTextComponentClass == nullptr) return;

	UPFPointsTextComponent* PointsTextComponent = NewObject<UPFPointsTextComponent>(this, PointsTextComponentClass);
	PointsTextComponent->RegisterComponent();
	PointsTextComponent->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PointsTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	PointsTextComponent->SetPointsText(AmountOfPoints);
}

void APFGoomba::DieTimerFinished()
{
	Die();
}
