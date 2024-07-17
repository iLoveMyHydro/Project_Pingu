// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystem/IceSpikes.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"

// Sets default values
AIceSpikes::AIceSpikes()
{

	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_PATH);
	MeshComponent->SetStaticMesh(mesh);
	RootComponent = MeshComponent;
	MeshComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	BoxCollision->bDynamicObstacle = true;
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(*PROJECTILE_MOVEMENT_NAME);
	ProjectileMovement->UpdatedComponent = BoxCollision;
	ProjectileMovement->InitialSpeed = 100.f;
	ProjectileMovement->MaxSpeed = 100.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

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
	if(!OtherActor && (OtherActor != this) && !OtherComp)
	{
		Destroy();
		if(OtherActor->IsA<AAIEnemy1>())
		{
			Enemy = CastChecked<AAIEnemy1>(OtherActor);
			Enemy->ApplyDamage(1);
		}
		else if(OtherActor->IsA<AAIBossEnemy1>())
		{
			BossEnemy = CastChecked<AAIBossEnemy1>(OtherActor);
			BossEnemy->ApplyDamage(1);
		}
	}
}

