// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystem/IceSpikes.h"

// Sets default values
AIceSpikes::AIceSpikes()
{
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_PATH);
	MeshComponent->SetStaticMesh(mesh);
	RootComponent = MeshComponent;
	MeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.4f));
	MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	BoxCollision->bDynamicObstacle = true;
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(*PROJECTILE_MOVEMENT_NAME);
	ProjectileMovement->InitialSpeed = 500.0f;
	ProjectileMovement->MaxSpeed = 700.0f;
}

// Called when the game starts or when spawned
void AIceSpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

