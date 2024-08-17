// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnSystem/RespawnPoint.h"

#include "GameModeBase/GameModeBaseCode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/InputController.h"
#include "Player/PinguCharacter.h"

// Sets default values
ARespawnPoint::ARespawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting the Box Collision
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

// Box Begin Overlap
void ARespawnPoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bSpawnPointSet = true;

	Character = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	GameMode = Cast<AGameModeBaseCode>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	InputController = Cast<AInputController>(Character->GetController());

	auto SpawnPoint = OtherActor->GetActorLocation();
	//GameMode->setplay(InputController , SpawnPoint);
}
