// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem/IceSpikeSpawn.h"

// Sets default values
AIceSpikeSpawn::AIceSpikeSpawn()
{
	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_NAME);

	Mesh->SetupAttachment(RootComponent);
	Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object);
	Mesh->SetMaterial(0, Material);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	Mesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	BoxCollision->bDynamicObstacle = true;
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
}

// Called when the game starts or when spawned
void AIceSpikeSpawn::BeginPlay()
{
	Super::BeginPlay();
}