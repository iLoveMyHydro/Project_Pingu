// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/AIEnemy1.h"
#include "Enemy/Controller/AIControllerAI1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OilBarrel/OilBarrel.h"

// Sets default values
AAIEnemy1::AAIEnemy1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//Todo: Add Scene Component -> Als Spawn Point

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(64.0f, 64.0f, 64.0f));
	CollisionMesh->SetHiddenInGame(false);

	AIControllerClass = ConstructorHelpers::FClassFinder<AAIController>(*FSM_CONTROLLER_PATH).Class;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AAIEnemy1::BeginPlay()
{
	Super::BeginPlay();

	auto controller = Cast<AAIControllerAI1>(GetController());
	controller->SetCharacter(this);
}

// Called every frame
void AAIEnemy1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemy1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemy1::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	if(Health <= 0)
	{
		AAIEnemy1::Destroy();
	}
}

