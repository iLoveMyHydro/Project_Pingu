// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InputController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PinguCharacter.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"
#include "GameFramework/Character.h"

class UEnhancedInputLocalPlayerSubsystem;

AInputController::AInputController()
{
	InitInputAction();
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}

void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInputController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AInputController::HandleStopMovement);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AInputController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AInputController::StopJump);

		//Slap Attack
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Started, this, &AInputController::HandleSlapAttack);
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Completed, this, &AInputController::HandleSlapAttackComplete);

		//Noot Noot Attack
		EnhancedInputComponent->BindAction(NootNootAction, ETriggerEvent::Started, this, &AInputController::HandleNootAttack);
	}
}

void AInputController::InitInputAction()
{
	DefaultMappingContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*IMC_PATH).Object;
	MoveAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_PATH).Object;
	JumpAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_JUMP_PATH).Object;
	SlapAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_SLAP_PATH).Object;
	NootNootAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_NOOT_PATH).Object;

}

void AInputController::Move(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();
	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, Speed, false);
}

void AInputController::Jump()
{
	auto* MyCharacter = GetPawn<ACharacter>();
	if (!IsValid(MyCharacter))
		return;
	MyCharacter->Jump();
}

void AInputController::StopJump()
{
	auto* MyCharacter = GetPawn<ACharacter>();
	if (!IsValid(MyCharacter))
		return;
	MyCharacter->StopJumping();
}

void AInputController::HandleStopMovement(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();

	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, 0, false);
}


void AInputController::HandleSlapAttack()
{
	//TODO: Animation ausführen
	//TODO: Apply Damage richtig einstellen

	if(!GetWorld()) return;

	auto OtherCharacter = CastChecked<APinguCharacter>(GetPawn())->GetOtherCharacter();
	if(OtherCharacter != nullptr)
	{
		if(OtherCharacter->IsA<AAIBossEnemy1>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Boss Enemy"));
			BossEnemy = CastChecked<AAIBossEnemy1>(OtherCharacter);
			BossEnemy->ApplyDamage(1);
		}
		if(OtherCharacter->IsA<AAIEnemy1>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy"));
			Enemy = CastChecked<AAIEnemy1>(OtherCharacter);
			Enemy->ApplyDamage(1);
		}
	}
}

void AInputController::HandleNootAttack()
{
	//TODO: Animation ausführen

	//if( PinguCharacter->GetIceSpikes() > 0 )
	//{
	//	PinguCharacter->ThrowIceSpikes();
	//}
}

void AInputController::HandleSlapAttackComplete()
{
	IsAttacking = false;
}
