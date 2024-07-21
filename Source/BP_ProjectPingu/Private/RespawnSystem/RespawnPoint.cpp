// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnSystem/RespawnPoint.h"

#include "GameModeBase/GameModeBaseCode.h"
#include "Player/PinguCharacter.h"

// Sets default values
ARespawnPoint::ARespawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ARespawnPoint::OnBoxBeginOverlap);
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(*ARROW_NAME);
}

// Called when the game starts or when spawned
void ARespawnPoint::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARespawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARespawnPoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bSpawnPointSet = true;

}
