// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/InputController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PinguCharacter.h"
#include "Enemy/Character/NormalEnemy.h"
#include "GameFramework/Character.h"
#include "Enemy/Character/BossEnemy.h"

class UEnhancedInputLocalPlayerSubsystem;

// Sets default values
AInputController::AInputController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitInputAction();
}

//Called when the game starts or when spawned
void AInputController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

//Binds the Input Actions to their related Methods
void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInputController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this,
		                                   &AInputController::HandleStartedMovement);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this,
		                                   &AInputController::HandleStopMovement);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AInputController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AInputController::StopJump);


		//Slap Attack
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Started, this,
		                                   &AInputController::HandleSlapAttack);
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Completed, this,
		                                   &AInputController::HandleSlapAttackComplete);

		//Noot Noot Attack
		EnhancedInputComponent->BindAction(NootNootAction, ETriggerEvent::Started, this,
		                                   &AInputController::HandleNootAttack);
	}
}

//Initialize the Mapping Context and the Input Actions
void AInputController::InitInputAction()
{
	DefaultMappingContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*IMC_PATH).Object;
	MoveAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_PATH).Object;
	JumpAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_JUMP_PATH).Object;
	SlapAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_SLAP_PATH).Object;
	NootNootAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_NOOT_PATH).Object;
	PauseAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_PAUSE_PATH).Object;
}

//Updates every frame
void AInputController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//When the Move Button is pressed
void AInputController::Move(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();
	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, Speed, false);
}

//When the Jump Button is pressed
void AInputController::Jump()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr)
	{
		return;
	}
	PinguCharacter->Jump();
}

//When the jump is done
void AInputController::StopJump()
{
	bIsJumping = false;
}

//When the Character is not walking
void AInputController::HandleStopMovement(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();

	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, 0, false);
}

//When the Slap Attack Button is pressed
void AInputController::HandleSlapAttack()
{
		if (!GetWorld())
		{
			return;
		}

		auto OtherCharacter = CastChecked<APinguCharacter>(GetPawn())->GetOtherCharacter();
		if (OtherCharacter != nullptr)
		{
			if (OtherCharacter->IsA<ANormalEnemy>())
			{
				UE_LOG(LogTemp, Warning, TEXT("Enemy"));
				Enemy = CastChecked<ANormalEnemy>(OtherCharacter);
				Enemy->ApplyDamage(1);
			}
			if (OtherCharacter->IsA<ABossEnemy>())
			{
				UE_LOG(LogTemp, Warning, TEXT("Boss Enemy"));
				BossEnemy = CastChecked<ABossEnemy>(OtherCharacter);
				BossEnemy->ApplyDamage(1);
			}
		}
}

//When the Noot Noot Attack Button is pressed
void AInputController::HandleNootAttack()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr)
	{
		return;
	}

	if (PinguCharacter->GetIceSpikes() > 0)
	{
		PinguCharacter->ThrowIceSpikes();
	}

	auto IceSpikes = PinguCharacter->GetIceSpikes();

	IceSpikes--;

	if (IceSpikes <= 0)
	{
		IceSpikes = 0;
	}
	PinguCharacter->SetIceSpikes(IceSpikes);
}

//When the Slap Attack is done 
void AInputController::HandleSlapAttackComplete()
{
	bIsAttacking = false;
}

//When the Move Button is pressed
void AInputController::HandleStartedMovement()
{
	PinguCharacter = Cast<APinguCharacter>(GetPawn());
	if (PinguCharacter == nullptr)
	{
		return;
	}

	bIsWalking = true;
}
