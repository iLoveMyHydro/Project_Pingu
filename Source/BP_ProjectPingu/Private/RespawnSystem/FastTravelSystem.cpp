// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnSystem/FastTravelSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFastTravelSystem::AFastTravelSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFastTravelSystem::TravelToPoint()
{
	Character = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	FRotator Rotation = Character->GetActorRotation();
	//Character->SetActorLocation(FTransform(Rotation));
}

// Called when the game starts or when spawned
void AFastTravelSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFastTravelSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

