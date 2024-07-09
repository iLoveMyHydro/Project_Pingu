// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"
#include "Camera/CameraComponent.h"
#include "DamageSystem/IceSpikes.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"
#include "Enemy/Controller/AIControllerAIBoss1.h"
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

	//IceSpikeMat = CreateDefaultSubobject<AIceSpikes>(*ICE_SPIKE_NAME);
	//IceSpikeMat->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//IceSpikeMat = GetWorld()->SpawnActor<AIceSpikes>(FVector::ZeroVector, FRotator::ZeroRotator);

	// Init Camera
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();

	// Init Player
	InitPlayer();
}

void APinguCharacter::ApplyDamage(int A_DamageAmount)
{
	A_DamageAmount -= A_DamageAmount;

	Health += A_DamageAmount;

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

void APinguCharacter::ThrowIceSpikes()
{
	//DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	
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

}

void APinguCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Respawn"));
	if(!GetWorld()) return;
	
	if(OtherActor->IsA<AAIEnemy1>())
	{
		OtherCharacter = CastChecked<AAIEnemy1>(OtherActor);
	}
	else if(OtherActor->IsA<AAIBossEnemy1>())
	{
		OtherCharacter = CastChecked<AAIBossEnemy1>(OtherActor);
	}
	//else if(OtherActor->IsA<AIceSpikes>())
	//{
	//	if(IceSpikes <= IceSpikesMax)
	//	{
	//		IceSpikes = IceSpikesMax;
	//	}
	//}
	IsColliding = true;
}