// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PinguCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


// Sets default values
APinguCharacter::APinguCharacter()
{
	Material = ConstructorHelpers::FObjectFinder<UMaterialInterface>(*MAT_PATH).Object;
	GetMesh()->SetSkeletalMesh(ConstructorHelpers::FObjectFinder<USkeletalMesh>(*MESH_PATH).Object);
	GetMesh()->SetMaterial(0, Material);
	if (!PinguCameraComponent) PinguCameraComponent = InitCamera();
	InitInputAction();

	//Init
	InitPlayer();
}

auto APinguCharacter::InitCamera() -> UCameraComponent*
{
	PinguCameraComponent = CreateDefaultSubobject<UCameraComponent>(*CAMERA_NAME);
	PinguCameraComponent->SetupAttachment(RootComponent);
	PinguCameraComponent->SetRelativeLocation(FVector(-500.0f, 0.0f, 150.0f));
	PinguCameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	PinguCameraComponent->bUsePawnControlRotation = false;
	return PinguCameraComponent;
}

void APinguCharacter::InitInputAction()
{
	if (!InputCtx) InputCtx = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*PLAYER_CTX_PATH).Object;
	if (!MoveActionRight) MoveActionRight = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_PATH).Object;
	if (!JumpAction) JumpAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_JUMP_PATH).Object;
}

void APinguCharacter::InitPlayer()
{
	Speed = 1;
	ACharacter::JumpMaxCount = 2;
	GetCharacterMovement()->JumpZVelocity = 300.0f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->GravityScale = 2.0f;
	FVector NewLocation(0.0f, 0.0f, 0.0f);
	FRotator NewRotation(0.0f, 0.0f, 0.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	UCharacterMovementComponent* const MovementComponent = GetCharacterMovement();

	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bUseControllerDesiredRotation = false;
	}
}

void APinguCharacter::CharacterForwardDirection(FVector& outForward)
{
	FRotator rotation = Controller->GetControlRotation();

	// Adjust the Yaw by 90 degrees to place the camera at a 90-degree angle to the character
	FRotator YawRotation = FRotator(0, rotation.Yaw + 90.0f, 0);

	// get forward vector in regard to the camera
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	outForward = ForwardDirection;
}


void APinguCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		FVector ForwardDirection;
		CharacterForwardDirection(ForwardDirection);
		AddMovementInput(ForwardDirection, Speed);
	}
}

void APinguCharacter::HandleStopMovement(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();
	FVector ForwardDirection;

	//Make the forward direction the direction the player is facing.
	AddMovementInput(ForwardDirection, InputPlayerMovement.X);
}

void APinguCharacter::HandleSlapAttack()
{

}

void APinguCharacter::HandleNootAttack()
{
}

//Called when the game starts or when spawned
void APinguCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputCtx, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller doesnt exist!"));
	}
}

//Called to bind functionality to input
void APinguCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		inputComponent->BindAction(MoveActionRight, ETriggerEvent::Triggered, this, &APinguCharacter::Move);
		inputComponent->BindAction(MoveActionRight, ETriggerEvent::Completed, this, &APinguCharacter::HandleStopMovement);

		//Jumping
		inputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		inputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Slap Attack
		inputComponent->BindAction(SlapAction, ETriggerEvent::Started, this, &APinguCharacter::HandleSlapAttack);


		//Noot Noot Attack
		inputComponent->BindAction(NootAction, ETriggerEvent::Started, this, &APinguCharacter::HandleNootAttack);

	}
}