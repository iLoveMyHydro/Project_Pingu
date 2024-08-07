// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Character/NormalEnemy.h"
#include "Enemy/Controller/NormalAIController.h"
#include "FiniteStateMachine/Machines/NormalSimpleFSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OilBarrel/OilBarrel.h"
#include "BP_ProjectPingu/Private/FiniteStateMachine/FSM/NormalFSM.h"
#include "Player/PinguCharacter.h"
#include "Player/InputController.h"


// Sets default values
ANormalEnemy::ANormalEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//Get Oil Barrel
	OilBarrelProjectile = ConstructorHelpers::FClassFinder<AOilBarrel>(*OIL_BARREL_PATH).Class;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(64.0f, 64.0f, 64.0f));
	CollisionMesh->SetHiddenInGame(false);

	SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("Perception Trigger"));
	SphereColl->SetSphereRadius(500);
	SphereColl->SetRelativeLocation(FVector(0, 0, 90));
	SphereColl->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereColl->SetHiddenInGame(true);
	SphereColl->OnComponentBeginOverlap.AddDynamic(this, &ANormalEnemy::OnCollision);
	SphereColl->OnComponentEndOverlap.AddDynamic(this, &ANormalEnemy::OnCollisionExit);
	SphereColl->SetupAttachment(GetMesh());

	SpawnLocationOilBarrel = CreateDefaultSubobject<USceneComponent>(*SPAWNLOCATION_OIL_BARREL_NAME);
	SpawnLocationOilBarrel->SetRelativeLocation(FVector(40.0f, 0.0f, 50.0f));
	SpawnLocationOilBarrel->SetupAttachment(RootComponent);

	AIControllerClass = ConstructorHelpers::FClassFinder<ANormalAIController>(*FSM_CONTROLLER_PATH).Class;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void ANormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<ANormalAIController>(GetController());
	Controller->SetCharacter(this);

	PlayerController = Cast<AInputController>(GetWorld()->GetFirstPlayerController());


	if (Fsm == nullptr)
	{
		Fsm = static_cast<NormalSimpleFSM*>(new NormalSimpleFSM(Controller));
	}
	if (Fsm != nullptr)
	{
		Fsm->Initialize();
	}
}

// Called every frame
void ANormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANormalEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANormalEnemy::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	if (Health <= 0)
	{
		ANormalEnemy::Destroy();
	}
}

void ANormalEnemy::ThrowOilBarrel()
{
	Character = GetController()->GetPawn<ANormalEnemy>();

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

//OnCollisionOverlap ->Add Dynamic richtige Hitbox -> if state schlag von pingu -> gib mir schaden

void ANormalEnemy::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()) && !PlayerController->IsPaused())
	{
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, [this]() {Fsm->Transition(static_cast<NormalSimpleFSM*>(Fsm)->GetThrowObjectState()); }, RespawnDelay, !PlayerController->IsPaused());
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Enter"));
	}
}

void ANormalEnemy::OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APinguCharacter::StaticClass()) && !PlayerController->IsPaused())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, TEXT("Exit"));
		Fsm->Transition(static_cast<NormalSimpleFSM*>(Fsm)->GetSearchPlayerState());
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	}
}
