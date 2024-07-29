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
#include "GUI/PauseMenu.h"

class UEnhancedInputLocalPlayerSubsystem;

AInputController::AInputController()
{
	InitInputAction();

	PauseMenuObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PAUSE_MENU_PATH).Class;

	PlayerHUDObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;
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

	if (PauseMenuObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("Pause Menu"));

		PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuObject, "Pause Menu");
		check(PauseMenu);

		PauseMenu->AddToPlayerScreen();
	}

	if (PlayerHUDObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("UI"));

		PlayerHUD = CreateWidget<UPlayerHUD>(this, PlayerHUDObject, "Player HUD");
		check(PlayerHUD);

		PlayerHUD->AddToPlayerScreen();

		PinguCharacter = GetPawn<APinguCharacter>();
		if (PinguCharacter == nullptr) return;


		PlayerHUD->SetIceSpikeAmount(PinguCharacter->GetIceSpikes(), 5);
	}
}

void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInputController::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AInputController::HandleStartedMovement);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AInputController::HandleStopMovement);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AInputController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AInputController::StopJump);

		//Slap Attack
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Started, this, &AInputController::HandleSlapAttack);
		EnhancedInputComponent->BindAction(SlapAction, ETriggerEvent::Completed, this, &AInputController::HandleSlapAttackComplete);

		//Noot Noot Attack
		EnhancedInputComponent->BindAction(NootNootAction, ETriggerEvent::Started, this, &AInputController::HandleNootAttack);

		//Pause Menu
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AInputController::HandlePauseAction);
	}
}

void AInputController::InitInputAction()
{
	DefaultMappingContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(*IMC_PATH).Object;
	MoveAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_MOVE_PATH).Object;
	JumpAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_JUMP_PATH).Object;
	SlapAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_SLAP_PATH).Object;
	NootNootAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_NOOT_PATH).Object;
	PauseAction = ConstructorHelpers::FObjectFinder<UInputAction>(*IA_PAUSE_PATH).Object;
}

void AInputController::Move(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();
	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, Speed, false);
}

void AInputController::Jump()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr) return;

	PinguCharacter->Jump();
	PinguCharacter->SetJumpAnimation();
}

void AInputController::StopJump()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr) return;

	PinguCharacter->StopJumping();
}

void AInputController::HandleStopMovement(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();

	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, 0, false);
	PinguCharacter->SetIdleAnimation();

}


void AInputController::HandleSlapAttack()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr) return;

	PinguCharacter->SetSlapAnimation();

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
		PinguCharacter->PlaySlapSound(); //This code has been brought to you by Hubsi
	}
}

void AInputController::HandleNootAttack()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr) return;

	if (PinguCharacter->GetIceSpikes() > 0)
	{
		PinguCharacter->ThrowIceSpikes();
		PinguCharacter->SetNootAnimation();
	}

	auto IceSpikes = PinguCharacter->GetIceSpikes();

	IceSpikes--;

	if(IceSpikes <= 0)
	{
		IceSpikes = 0;
	}

	PlayerHUD->SetIceSpikeAmount(IceSpikes, 5);
	PinguCharacter->SetIceSpikes(IceSpikes);


}

void AInputController::HandleSlapAttackComplete()
{
	IsAttacking = false;
}

void AInputController::HandlePauseAction()
{
	AInputController* const PlayerController = Cast<AInputController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (PlayerController != nullptr)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetPause(true);
	}
}

void AInputController::HandleStartedMovement()
{
	PinguCharacter = Cast<APinguCharacter>(GetPawn());
	if (PinguCharacter == nullptr) return;

	PinguCharacter->SetWalkAnimation();
}
