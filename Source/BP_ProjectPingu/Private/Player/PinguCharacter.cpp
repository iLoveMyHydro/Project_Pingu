// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"

#include "InputController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DamageSystem/IceSpikeSpawn.h"
#include "Enemy/Character/NormalEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageSystem/Spike.h"
#include "RespawnSystem/RespawnPoint.h"
#include "HUD/PlayerHUD.h"

//Audio Hubsi here again
#include "Components/AudioComponent.h"

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

	//Get the Animations
	IdleAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*IDLE_ANIM_PATH).Object;
	WalkAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*WALK_ANIM_PATH).Object;
	NootAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*NOOT_ANIM_PATH).Object;
	JumpAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*JUMP_ANIM_PATH).Object;
	SlapAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*SLAP_ANIM_PATH).Object;

	//Start Idle Animation
	GetMesh()->PlayAnimation(IdleAnim, true);

	//Get the Collision Box
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(100.0f, 60.0f, 100.0f));
	CollisionMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CollisionMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	//Get IceSpikes
	IceSpikeProjectile = ConstructorHelpers::FClassFinder<AIceSpikes>(*ICE_SPIKE_PATH).Class;

	// Init Camera
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();

	// Init Player
	InitPlayer();

	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(0.0f, 0.0f, 0.0f);

	//Get HUD Object
	PlayerHUDObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;

	SpawnLocationIceSpike = CreateDefaultSubobject<USceneComponent>(*SPAWNLOCATION_ICE_SPIKE_NAME);
	SpawnLocationIceSpike->SetRelativeLocation(FVector(40.0f, 0.0f, 50.0f));
	SpawnLocationIceSpike->SetupAttachment(RootComponent);

	//Set up Audio Components (Hubsi-code)
	AttackSFXComponent = CreateDefaultSubobject<UAudioComponent>(*ATTACK_SFX_NAME);
	DamageSFXComponent = CreateDefaultSubobject<UAudioComponent>(*DAMAGE_SFX_NAME);
	FootstepSFXComponent = CreateDefaultSubobject<UAudioComponent>(*FOOTSTEPS_SFX_NAME);

	AttackSFXComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*ATTACK_SFX_PATH).Object);
	DamageSFXComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*DAMAGE_SFX_PATH).Object);
	FootstepSFXComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*FOOTSTEPS_SFX_PATH).Object);

	AttackSFXComponent->SetAutoActivate(bAutoActivate);
	DamageSFXComponent->SetAutoActivate(bAutoActivate);
	FootstepSFXComponent->SetAutoActivate(bAutoActivate);

	AttackSFXComponent->SetupAttachment(RootComponent);
	DamageSFXComponent->SetupAttachment(RootComponent);
	FootstepSFXComponent->SetupAttachment(RootComponent);
}

void APinguCharacter::ApplyDamage(int A_DamageAmount)
{
	Health -= A_DamageAmount;

	PlayerHUD->SetLifeAmount(Health, MaxHealth);

	PlayDamageSound(); //Hubsi strikes again

	if (Health <= 0)
	{
		AInputController* const PlayerController = Cast<AInputController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (PlayerController != nullptr)
		{
			PlayerController->SetPause(true);
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &APinguCharacter::Respawn, RespawnDelay, false);
			PlayerHUD->SetLifeAmount(MaxHealth, MaxHealth);
			PlayerController->SetPause(false);
		}
	}
}

bool APinguCharacter::GetIsColliding()
{
	return IsColliding;
}

ACharacter* APinguCharacter::GetOtherCharacter()
{
	return OtherCharacter;
}

int APinguCharacter::GetIceSpikes()
{
	return IceSpikes;
}

void APinguCharacter::SetIceSpikes(int A_IceSpikes)
{
	IceSpikes = A_IceSpikes;
}

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
			PlayNootNootSound();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
}

bool APinguCharacter::GetGotIceSpikes()
{
	return bGotIceSpikes;
}

APinguCharacter& APinguCharacter::SetIdleAnimation()
{
	GetMesh()->PlayAnimation(IdleAnim, true);
	return *this;
}

APinguCharacter& APinguCharacter::SetNootAnimation()
{
	GetMesh()->PlayAnimation(NootAnim, false);
	return *this;
}

APinguCharacter& APinguCharacter::SetWalkAnimation()
{
	GetMesh()->PlayAnimation(WalkAnim, true);
	return *this;
}

APinguCharacter& APinguCharacter::SetJumpAnimation()
{
	GetMesh()->PlayAnimation(JumpAnim, false);
	return *this;
}

APinguCharacter& APinguCharacter::SetSlapAnimation()
{
	GetMesh()->PlayAnimation(SlapAnim, false);
	return *this;
}

void APinguCharacter::Respawn()
{
	SetActorLocation(SpawnLocation);
	Health = 3;
}

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

	if(PlayerHUDObject && IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("UI"));
		AInputController* PlayerController = GetController<AInputController>();
		check(PlayerController);

		PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDObject, "Player HUD");
		check(PlayerHUD);

		PlayerHUD->AddToPlayerScreen();
		PlayerHUD->SetLifeAmount(MaxHealth, MaxHealth);
		PlayerHUD->SetIceSpikeAmount(IceSpikes, IceSpikesMax);
	}

	SetIdleAnimation();

	SpawnLocation = GetActorLocation();
}

void APinguCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!GetWorld()) return;
	
	if(OtherActor->IsA<ANormalEnemy>())
	{
		OtherCharacter = CastChecked<ANormalEnemy>(OtherActor);
	}
	else if(OtherActor->IsA<AIceSpikeSpawn>())
	{
		bGotIceSpikes = true;
		if(IceSpikes <= IceSpikesMax)
		{
			IceSpikes = IceSpikesMax;
			PlayerHUD->SetIceSpikeAmount(IceSpikes, IceSpikesMax);
		}
	}
	else if(OtherActor->IsA<ARespawnPoint>())
	{
		SpawnLocation = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Neuer SpawnPoint"));
	}
	else if(OtherActor->IsA<ASpike>())
	{
		ApplyDamage(1);
	}
	IsColliding = true;
}

//audio methods from header file, you guessed it, Hubsi did this

void APinguCharacter::PlaySlapSound()
{
	if (!AttackSFXComponent) return;
	if (!AttackSFXComponent->GetSound()) return;

	if (AttackSFXComponent->IsActive() == false) AttackSFXComponent->SetActive(true);
	if (AttackSFXComponent->IsPlaying() == false) AttackSFXComponent->Play();

	AttackSFXComponent->SetTriggerParameter(*MELEE_ATTACK_TRIGGER_NAME);
}

void APinguCharacter::PlayNootNootSound()
{
	if (!AttackSFXComponent) return;
	if (!AttackSFXComponent->GetSound()) return;

	if (AttackSFXComponent->IsActive() == false) AttackSFXComponent->SetActive(true);
	if (AttackSFXComponent->IsPlaying() == false) AttackSFXComponent->Play();

	AttackSFXComponent->SetTriggerParameter(*RANGED_ATTACK_TRIGGER_NAME);
}

void APinguCharacter::PlayDamageSound()
{
	if (!DamageSFXComponent) return;
	if (!DamageSFXComponent->GetSound()) return;

	if (DamageSFXComponent->IsActive() == false) DamageSFXComponent->SetActive(true);
	if (DamageSFXComponent->IsPlaying() == false) DamageSFXComponent->Play();

	DamageSFXComponent->SetTriggerParameter(*DAMAGE_TRIGGER_NAME);
}

void APinguCharacter::PlayFootstepSound()
{
	if (!FootstepSFXComponent) return;
	if (!FootstepSFXComponent->GetSound()) return;

	if (FootstepSFXComponent->IsActive() == false) FootstepSFXComponent->SetActive(true);
	if (FootstepSFXComponent->IsPlaying() == false) FootstepSFXComponent->Play();

	FootstepSFXComponent->SetTriggerParameter(*FOOTSTEP_TRIGGER_NAME);
}