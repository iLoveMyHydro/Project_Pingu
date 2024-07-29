// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystem/IceSpikes.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"
#include  "Components/SphereComponent.h"

// Sets default values
AIceSpikes::AIceSpikes()
{
	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object);
	Mesh->SetMaterial(0, Material);
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	Mesh->OnComponentHit.AddDynamic(this, &AIceSpikes::OnHit);

	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(*PROJECTILE_MOVEMENT_NAME);
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 1500.0f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = false;
	ProjectileMovement->ProjectileGravityScale = 0.5f;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AIceSpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIceSpikes::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != nullptr) && (OtherActor != this))
	{

		if(OtherActor->IsA<AAIEnemy1>())
		{
			Enemy = CastChecked<AAIEnemy1>(OtherActor);
			Enemy->ApplyDamage(1);
			Destroy();
		}
		else if(OtherActor->IsA<AAIBossEnemy1>())
		{
			BossEnemy = CastChecked<AAIBossEnemy1>(OtherActor);
			BossEnemy->ApplyDamage(1);
			Destroy();
		}
	}
}