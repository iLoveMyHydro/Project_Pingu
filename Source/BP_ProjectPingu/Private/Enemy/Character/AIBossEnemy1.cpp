// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Controller/AIControllerAIBoss1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PinguCharacter.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "FiniteStateMachine/Machines/SimpleFSMAI1.h"
#include "OilBarrel/OilBarrel.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "FiniteStateMachine/State/StateAI1.h"
#include "Components/SphereComponent.h"


// Sets default values
AAIBossEnemy1::AAIBossEnemy1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f,0.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//Get Oil Barrel
	OilBarrelProjectile = ConstructorHelpers::FClassFinder<AOilBarrel>(*OIL_BARREL_PATH).Class;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(64.0f, 64.0f, 64.0f));
	CollisionMesh->SetHiddenInGame(false);

	sphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("Perception Trigger"));
	sphereColl->SetSphereRadius(500);
	sphereColl->SetRelativeLocation(FVector(0, 0, 90));
	sphereColl->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	sphereColl->SetHiddenInGame(false);
	sphereColl->OnComponentBeginOverlap.AddDynamic(this, &AAIBossEnemy1::OnCollision);
	sphereColl->OnComponentEndOverlap.AddDynamic(this, &AAIBossEnemy1::OnCollisionExit);
	sphereColl->SetupAttachment(GetMesh());

	AIControllerClass = ConstructorHelpers::FClassFinder<AAIController>(*FSM_CONTROLLER_PATH).Class;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AAIBossEnemy1::BeginPlay()
{
	Super::BeginPlay();

	auto controller = Cast<AAIControllerAIBoss1>(GetController());
	controller->SetCharacter(this);
}

// Called every frame
void AAIBossEnemy1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIBossEnemy1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBossEnemy1::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	if (Health <= 0)
	{
		AAIBossEnemy1::Destroy();
	}
}

void AAIBossEnemy1::ThrowOilBarrel()
{
	Character = GetController()->GetPawn<AAIBossEnemy1>();

	if (OilBarrelProjectile != nullptr)
	{
		//Aus FirstPlayer UE Demo
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FRotator Rotator = GetActorRotation();

			if (Rotator.Yaw >= 90.0f)
			{
				World->SpawnActor<AOilBarrel>(OilBarrelProjectile, Character->GetActorLocation() + FVector(-70.0f, 0.0f, 50.0f), FRotator(0.0f, 90.0f, 0.0f), ActorSpawnParams);
			}
			else
			{
				World->SpawnActor<AOilBarrel>(OilBarrelProjectile, Character->GetActorLocation() + FVector(70.0f, 0.0f, 50.0f), FRotator(0.0f, -90.0f, 0.0f), ActorSpawnParams);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
}

void AAIBossEnemy1::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()))
	{
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, [this]() {Fsm->Transition(static_cast<SimpleFSMAI1*>(Fsm)->GetThrowObjectState()); }, RespawnDelay, true);
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Enter"));
	}
}

void AAIBossEnemy1::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Exit"));
		Fsm->Transition(static_cast<SimpleFSMAI1*>(Fsm)->GetSearchPlayerState());
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	}
}