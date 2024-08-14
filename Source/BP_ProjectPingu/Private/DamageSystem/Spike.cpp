// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem/Spike.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpike::ASpike()
{
    Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_NAME);

    Mesh->SetupAttachment(RootComponent);
    Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object);
    Mesh->SetMaterial(0, Material);

	//Get the Collision Box
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(Mesh);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(90.0f,90.0f, 20.0f));
	CollisionMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	CollisionMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
	
}

