// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/OilBarrel/OilBarrel.h"

// Sets default values
AOilBarrel::AOilBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AOilBarrel::Throw()
{
	//DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	//Speed -= LowSpeed;
}

// Called when the game starts or when spawned
void AOilBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOilBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

