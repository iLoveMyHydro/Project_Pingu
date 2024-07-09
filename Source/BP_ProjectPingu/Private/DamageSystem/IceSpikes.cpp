// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageSystem/IceSpikes.h"

// Sets default values
AIceSpikes::AIceSpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(*BOX_NAME);
	//BoxCollision->bDynamicObstacle = true;
	//BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->SetGenerateOverlapEvents(true);
	//BoxCollision->SetBoxExtent(FVector(32.0f, 60.0f, 32.0f));
}

// Called when the game starts or when spawned
void AIceSpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIceSpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

