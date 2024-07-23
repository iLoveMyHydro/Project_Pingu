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


// Sets default values
APinguCharacter::APinguCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(32.0f, 90.0f);

	Material = ConstructorHelpers::FObjectFinder<UMaterial>(*MAT_PATH).Object;
	SuperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(*MESH_NAME);
	SuperMesh->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	SuperMesh->SetupAttachment(RootComponent);
	SuperMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SuperMesh->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
	SuperMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	SuperMesh->SetMaterial(0, Material);

	IdleAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*IDLE_ANIM_PATH).Object;
	WalkAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*WALK_ANIM_PATH).Object;
	NootAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*NOOT_ANIM_PATH).Object;
	JumpAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*JUMP_ANIM_PATH).Object;
	SlapAnim = ConstructorHelpers::FObjectFinder<UAnimSequence>(*SLAP_ANIM_PATH).Object;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(32.0f, 60.0f, 32.0f));
	CollisionMesh->SetRelativeLocation(FVector(72.0f, 0.0f, 0.0f));
	CollisionMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	IceSpikeActor = ConstructorHelpers::FClassFinder<AIceSpikes>(*ICE_SPIKE_PATH).Class;

	// Init Camera
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();

	// Init Player
	InitPlayer();

	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(0.0f, 0.0f, 0.0f);

	PlayerHUDObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;
}

void APinguCharacter::ApplyDamage(int A_DamageAmount)
{
	A_DamageAmount -= A_DamageAmount;

	Health += A_DamageAmount;

	PlayerHUD->SetLifeAmount(Health, MaxHealth);

	if (Health <= 0)
	{
		APinguCharacter::Destroy();
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

	//Aus FirstPlayer UE Demo
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying;
		AInputController* PlayerController = Cast<AInputController>(Character->GetController());
		FRotator SpawnRotation = GetCharacterMovement()->GetLastUpdateRotation();

		//if(SpawnRotation == FRotator(0.0f,0.0f,0.0f))
		//{
		//	SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		//}
		//else if (SpawnRotation == FRotator(0.0f, 180.0f, 0.0f))
		//{
		//	SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		//}
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = (GetOwner()->GetActorLocation()) + SpawnRotation.RotateVector(MuzzleOffset);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AIceSpikes>(IceSpikeActor, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

APinguCharacter& APinguCharacter::SetIdleAnimation()
{
	SuperMesh->PlayAnimation(IdleAnim, true);
	return *this;
}

APinguCharacter& APinguCharacter::SetNootAnimation()
{
	SuperMesh->PlayAnimation(NootAnim, false);
	return *this;
}

APinguCharacter& APinguCharacter::SetWalkAnimation()
{
	SuperMesh->PlayAnimation(WalkAnim, true);
	return *this;
}

APinguCharacter& APinguCharacter::SetJumpAnimation()
{
	SuperMesh->PlayAnimation(JumpAnim, false);
	return *this;
}

APinguCharacter& APinguCharacter::SetSlapAnimation()
{
	SuperMesh->PlayAnimation(SlapAnim, false);
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
		PlayerHUD->SetIceSpikeAmount(5, 5);
	}

	SuperMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);;
	SuperMesh->PlayAnimation(IdleAnim, true);
	SuperMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SuperMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	SuperMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
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
		}
	}
	IsColliding = true;
}