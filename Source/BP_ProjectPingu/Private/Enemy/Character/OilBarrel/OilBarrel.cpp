// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/OilBarrel/OilBarrel.h"
#include "Player/PinguCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AOilBarrel::AOilBarrel()
{
	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object);
	Mesh->SetMaterial(0, Material);
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	Mesh->OnComponentHit.AddDynamic(this, &AOilBarrel::OnHit);

	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(*PROJECTILE_MOVEMENT_NAME);
	ProjectileMovement->InitialSpeed = 750.0f;
	ProjectileMovement->MaxSpeed = 750.0f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = false;
	ProjectileMovement->ProjectileGravityScale = 0.5f;

	InitialLifeSpan = 3.0f;
}

void AOilBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{

		if (OtherActor->IsA<APinguCharacter>())
		{
			PinguCharacter = CastChecked<APinguCharacter>(OtherActor);
			PinguCharacter->ApplyDamage(1);
			Destroy();
		}
	}
}
