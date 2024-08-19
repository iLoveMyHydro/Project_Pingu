// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"

#include "InputController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DamageSystem/IceSpikeSpawn.h"
#include "Enemy/Character/NormalEnemy.h"
#include "Enemy/Character/BossEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RespawnSystem/RespawnPoint.h"

// Sets default values
APinguCharacter::APinguCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 90.0f);

	//Create Material and Mesh
	Material = ConstructorHelpers::FObjectFinder<UMaterial>(*MAT_PATH).Object;
	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetMesh()->SetMaterial(0, Material);

	//Get the Collision Box
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(100.0f, 60.0f, 80.0f));

	//Get IceSpikes
	IceSpikeProjectile = ConstructorHelpers::FClassFinder<AIceSpikes>(*ICE_SPIKE_PATH).Class;

	// Init Camera
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();

	// Init Player
	InitPlayer();

	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(0.0f, 0.0f, 0.0f);

	SpawnLocationIceSpike = CreateDefaultSubobject<USceneComponent>(*SPAWNLOCATION_ICE_SPIKE_NAME);
	SpawnLocationIceSpike->SetRelativeLocation(FVector(40.0f, 0.0f, 50.0f));
	SpawnLocationIceSpike->SetupAttachment(RootComponent);
}

//If the Player get hits by something he will get damage
//If the Player has no Life left - he will be respawned 
void APinguCharacter::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	if (Health <= 0)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		AInputController* const PlayerController = Cast<AInputController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (PlayerController != nullptr)
		{
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &APinguCharacter::Respawn, RespawnDelay, false);
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
	}
}

// Returns bool if player is colliding
bool APinguCharacter::GetIsColliding()
{
	return IsColliding;
}

// Returns other Character
ACharacter* APinguCharacter::GetOtherCharacter()
{
	return OtherCharacter;
}

// Get Ice Spike Value
int APinguCharacter::GetIceSpikes()
{
	return IceSpikes;
}

// Set Ice Spike Value
void APinguCharacter::SetIceSpikes(int A_IceSpikes)
{
	IceSpikes = A_IceSpikes;
}

//Spawns the Ice Spikes with the correct Rotation and Location
void APinguCharacter::ThrowIceSpikes()
{

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn())
	{
		Character = Cast<APinguCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	}

	if(IceSpikeProjectile != nullptr)
	{
		//Aus FirstPlayer UE Demo
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			FRotator Rotator = GetActorRotation();

			if(Rotator.Yaw >= 90.0f)
			{
				World->SpawnActor<AIceSpikes>(IceSpikeProjectile, Character->GetActorLocation() + FVector(-70.0f, 0.0f, 50.0f), FRotator(0.0f, 90.0f, 0.0f), ActorSpawnParams);
			}
			else
			{
				World->SpawnActor<AIceSpikes>(IceSpikeProjectile, Character->GetActorLocation() + FVector(70.0f, 0.0f, 50.0f), FRotator(0.0f, -90.0f, 0.0f), ActorSpawnParams);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
}

// Returns bool if got Ice Spike
bool APinguCharacter::GetGotIceSpikes()
{
	return bGotIceSpikes;
}

//When the player has no life left, he will be respawned
void APinguCharacter::Respawn()
{
	SetActorLocation(SpawnLocation);
	Health = 3;
}

//Initialize some STats for the Camera
auto APinguCharacter::InitCamera() -> UCameraComponent*
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(*CAMERA_ARM_NAME);
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); //No Rotation when Character does
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.0f;

	PinguCameraComponent = CreateDefaultSubobject<UCameraComponent>(*CAMERA_NAME);
	PinguCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PinguCameraComponent->bUsePawnControlRotation = false;

	return PinguCameraComponent;
}

//Initialize some Stats for the player
void APinguCharacter::InitPlayer()
{
	ACharacter::JumpMaxCount = 2;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	bGotIceSpikes = false;
}

//Called when the game starts or when spawned
void APinguCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &APinguCharacter::OnBoxBeginOverlap);

	SpawnLocation = GetActorLocation();
}

//When somethings Overlaps with the Box Collision
void APinguCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!GetWorld()) return;
	
	if(OtherActor->IsA<ANormalEnemy>())
	{
		OtherCharacter = CastChecked<ANormalEnemy>(OtherActor);
	}
	else if(OtherActor->IsA<ABossEnemy>())
	{
		OtherCharacter = CastChecked<ABossEnemy>(OtherActor);
	}
	else if(OtherActor->IsA<AIceSpikeSpawn>())
	{
		bGotIceSpikes = true;
		if(IceSpikes <= IceSpikesMax)
		{
			IceSpikes = IceSpikesMax;
		}
	}
	else if(OtherActor->IsA<ARespawnPoint>())
	{
		SpawnLocation = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Neuer SpawnPoint"));
	}
	IsColliding = true;
}