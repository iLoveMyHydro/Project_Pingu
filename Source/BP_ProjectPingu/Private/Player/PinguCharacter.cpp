// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"

#include "InputController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DamageSystem/IceSpikeSpawn.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageSystem/MyProject3Projectile.h"

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
	//SuperMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
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
	CollisionMesh->SetBoxExtent(FVector(90.0f, 60.0f, 32.0f));
	CollisionMesh->SetRelativeLocation(FVector(72.0f, 0.0f, 0.0f));
	CollisionMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));

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

	//Get Stimuli Source for AI
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(*STIMULI_NAME);
	StimuliSource->bAutoRegister = true;

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
	A_DamageAmount -= A_DamageAmount;

	Health += A_DamageAmount;

	PlayerHUD->SetLifeAmount(Health, MaxHealth);

	PlayDamageSound(); //Hubsi strikes again

	if (Health <= 0)
	{
		APinguCharacter::Destroy();
		//TODO: Respawn Bildschirm einblenden - am RespawnPoint spawnen lassen
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

	if(ProjectileClass != nullptr)
	{
		//Aus FirstPlayer UE Demo
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AMyProject3Projectile>(ProjectileClass, Character->GetActorLocation() + FVector(-60.0f, 0.0f, 50.0f), Character->GetViewRotation(), ActorSpawnParams);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile"));
	}
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
	PlayAttackSound(); //Hubsi Test
	return *this;
}

auto APinguCharacter::InitCamera() -> UCameraComponent*
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(*CAMERA_ARM_NAME);
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); //No Rotation when Character does
	CameraBoom->TargetArmLength = 500.0f;
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
	GetCharacterMovement()->JumpZVelocity = 300.0f;
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
		PlayerHUD->SetIceSpikeAmount(0, 5);
	}

	SetIdleAnimation();
}

void APinguCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!GetWorld()) return;
	
	if(OtherActor->IsA<AAIEnemy1>())
	{
		OtherCharacter = CastChecked<AAIEnemy1>(OtherActor);
	}
	else if(OtherActor->IsA<AAIBossEnemy1>())
	{
		OtherCharacter = CastChecked<AAIBossEnemy1>(OtherActor);
	}
	else if(OtherActor->IsA<AIceSpikeSpawn>())
	{
		if(IceSpikes <= IceSpikesMax)
		{
			IceSpikes = IceSpikesMax;
			PlayerHUD->SetIceSpikeAmount(IceSpikes, IceSpikesMax);
		}
	}
	IsColliding = true;
}

//audio methods from header file, you guessed it, Hubsi did this

void APinguCharacter::PlayAttackSound()
{
	if (!AttackSFXComponent) return;
	if (!AttackSFXComponent->GetSound()) return;

	if (AttackSFXComponent->IsActive() == false) AttackSFXComponent->SetActive(true);
	if (AttackSFXComponent->IsPlaying() == false) AttackSFXComponent->Play();

	AttackSFXComponent->SetTriggerParameter(*MELEE_ATTACK_TRIGGER_NAME);
}

void APinguCharacter::PlayDamageSound()
{
	if (!DamageSFXComponent) return;
	if (!DamageSFXComponent->GetSound()) return;

	if (DamageSFXComponent->IsActive() == false) DamageSFXComponent->SetActive(true);
	if (DamageSFXComponent->IsPlaying() == false) DamageSFXComponent->Play();

	DamageSFXComponent->SetTriggerParameter(*DAMAGE_TRIGGER_NAME);
}