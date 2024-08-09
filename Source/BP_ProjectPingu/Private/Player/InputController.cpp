// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InputController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PinguCharacter.h"
#include "Enemy/Character/NormalEnemy.h"
#include "GameFramework/Character.h"
#include "GUI/PauseMenu.h"
#include "HUD/PlayerHUD.h"
#include "Enemy/Character/BossEnemy.h"

//Audio Hubsi here again
#include "Components/AudioComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

AInputController::AInputController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitInputAction();

	//PauseMenuObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PAUSE_MENU_PATH).Class;

	PlayerHUDObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;

	//Audio Code by Hubsi
	MusicComponent = CreateDefaultSubobject<UAudioComponent>(*MUSIC_NAME);
	MusicComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*MUSIC_PATH).Object);
	MusicComponent->SetAutoActivate(bAutoActivate);
	MusicComponent->SetupAttachment(RootComponent);
}

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	//Hubsi
	PlayLevelTheme();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
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

void AInputController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SlapCoolDown -= DeltaSeconds;
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
	if(SlapCoolDown <= 0)
	{
		PinguCharacter = GetPawn<APinguCharacter>();
		if (PinguCharacter == nullptr) return;

		PinguCharacter->SetSlapAnimation();

		if (!GetWorld()) return;

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
			PinguCharacter->PlaySlapSound(); //This code has been brought to you by Hubsi
		}
		SlapCoolDown = SlapCoolDownTime;
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
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		PauseLevelTheme();
	}
}

void AInputController::HandleStartedMovement()
{
	PinguCharacter = Cast<APinguCharacter>(GetPawn());
	if (PinguCharacter == nullptr) return;

	PinguCharacter->SetWalkAnimation();
}

void AInputController::PlayLevelTheme()
{
	if (!MusicComponent) return;
	if (!MusicComponent->GetSound()) return;

	if (MusicComponent->IsActive() == false) MusicComponent->SetActive(true);
	if (MusicComponent->IsPlaying() == false) MusicComponent->Play();

	MusicComponent->SetTriggerParameter(*MUSIC_TRIGGER_NAME);
}

void AInputController::PauseLevelTheme()
{
	if (!MusicComponent) return;
	if (!MusicComponent->GetSound()) return;

	if (MusicComponent->IsActive() == false) MusicComponent->SetActive(true);
	if (MusicComponent->IsPlaying() == false) MusicComponent->Play();

	MusicComponent->SetTriggerParameter(*PAUSE_MUSIC_TRIGGER_NAME);
}
