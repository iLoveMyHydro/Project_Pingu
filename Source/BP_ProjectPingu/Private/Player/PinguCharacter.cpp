// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APinguCharacter::APinguCharacter()
{
	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetMaterial(0, Material);

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(*BOX_COLLISION_NAME);
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetBoxExtent(FVector(32.0f, 60.0f, 32.0f));

	// Init Camera
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();

	// Init Player
	InitPlayer();
}

void APinguCharacter::ApplyDamage(int A_DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage"));
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
}

