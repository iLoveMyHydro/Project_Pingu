// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem/Spike.h"

// Sets default values
ASpike::ASpike()
{
    // Setting the Material and the Mesh
    Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(*MESH_NAME);

    Mesh->SetupAttachment(RootComponent);
    Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(*MESH_PATH).Object);
    Mesh->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
}