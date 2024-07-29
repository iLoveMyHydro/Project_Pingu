// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject3Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AMyProject3Projectile::AMyProject3Projectile() 
{
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_PATH);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	BoxCollision->bDynamicObstacle = true;
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	BoxCollision->OnComponentHit.AddDynamic(this, &AMyProject3Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	BoxCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	BoxCollision->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = BoxCollision;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = BoxCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AMyProject3Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) )
	{
		Destroy();
	}
}