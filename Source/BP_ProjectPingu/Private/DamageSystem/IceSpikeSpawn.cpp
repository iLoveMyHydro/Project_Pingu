// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem/IceSpikeSpawn.h"

// Sets default values
AIceSpikeSpawn::AIceSpikeSpawn()
{

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	BoxCollision->bDynamicObstacle = true;
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetBoxExtent(FVector(32.0f, 60.0f, 32.0f));
}

// Called when the game starts or when spawned
void AIceSpikeSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}