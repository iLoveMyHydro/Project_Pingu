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
#include "GUI/OptionMenu.h"
#include "HUD/PlayerHUD.h"
#include "Enemy/Character/BossEnemy.h"

//Audio Hubsi here again
#include "Components/AudioComponent.h"
#include "GameFramework/PawnMovementComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

// Sets default values
AInputController::AInputController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitInputAction();

	PauseMenuObject = ConstructorHelpers::FClassFinder<UPauseMenu>(*PAUSE_MENU_PATH).Class;

	OptionMenuObject = ConstructorHelpers::FClassFinder<UOptionMenu>(*OPTION_MENU_PATH).Class;

	PlayerHUDObject = ConstructorHelpers::FClassFinder<UPlayerHUD>(*PLAYER_HUD_PATH).Class;

	//Audio Code by Hubsi
	MusicComponent = CreateDefaultSubobject<UAudioComponent>(*MUSIC_NAME);
	MusicComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*MUSIC_PATH).Object);
	MusicComponent->SetAutoActivate(bAutoActivate);
	MusicComponent->SetUISound(true);
	MusicComponent->SetupAttachment(RootComponent);

	UISFXComponent = CreateDefaultSubobject<UAudioComponent>(*UI_NAME);
	UISFXComponent->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(*UI_PATH).Object);
	UISFXComponent->SetAutoActivate(bAutoActivate);
	UISFXComponent->SetUISound(true);
	UISFXComponent->SetupAttachment(RootComponent);
}

//Called when the game starts or when spawned
void AInputController::BeginPlay()
{
	Super::BeginPlay();

	//Hubsi
	PlayLevelTheme();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (PauseMenuObject)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("Pause Menu"));

		PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuObject, "Pause Menu");
		check(PauseMenu);

		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		PauseMenu->AddToPlayerScreen();
	}

	if (PlayerHUDObject)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("UI"));

		PlayerHUD = CreateWidget<UPlayerHUD>(this, PlayerHUDObject, "Player HUD");
		check(PlayerHUD);

		PlayerHUD->AddToPlayerScreen();

		PinguCharacter = GetPawn<APinguCharacter>();
		if (PinguCharacter == nullptr)
		{
			return;
		}


		PlayerHUD->SetIceSpikeAmount(PinguCharacter->GetIceSpikes(), 5);
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

		//Pause Menu
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this,
		                                   &AInputController::HandlePauseAction);
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

	SlapCoolDown -= DeltaSeconds;
}

//When the Move Button is pressed
void AInputController::Move(const FInputActionValue& Value)
{
	const FVector2D InputPlayerMovement = Value.Get<FVector2D>();
	FVector InputVector = FVector(InputPlayerMovement, 0);

	GetCharacter()->AddMovementInput(InputVector, Speed, false);
	bIsWalking = true;
}

//When the Jump Button is pressed
void AInputController::Jump()
{
	PinguCharacter = GetPawn<APinguCharacter>();
	if (PinguCharacter == nullptr)
	{
		return;
	}

	bIsJumping = true;
	PinguCharacter->Jump();
	PinguCharacter->PlayJumpSound();
	PinguCharacter->SetJumpAnimation();
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
	bIsWalking = false;
	AnimationHandler();
}

//When the Slap Attack Button is pressed
void AInputController::HandleSlapAttack()
{
	if (SlapCoolDown <= 0)
	{
		bIsAttacking = true;
		PinguCharacter = GetPawn<APinguCharacter>();
		if (PinguCharacter == nullptr)
		{
			return;
		}

		PinguCharacter->SetSlapAnimation();

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
			PinguCharacter->PlaySlapSound(); //This code has been brought to you by Hubsi
		}
		SlapCoolDown = SlapCoolDownTime;
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
		PinguCharacter->SetNootAnimation();
	}

	auto IceSpikes = PinguCharacter->GetIceSpikes();

	IceSpikes--;

	if (IceSpikes <= 0)
	{
		IceSpikes = 0;
	}

	PlayerHUD->SetIceSpikeAmount(IceSpikes, 5);
	PinguCharacter->SetIceSpikes(IceSpikes);
}

//When the Slap Attack is done 
void AInputController::HandleSlapAttackComplete()
{
	bIsAttacking = false;
}

//When this Button is pressed
void AInputController::HandlePauseAction()
{
	AInputController* const PlayerController = Cast<AInputController>(
		GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (PlayerController != nullptr)
	{
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetPause(true);
		//Code from Hubsi
		PauseLevelTheme();
		PlayUIOpenSound();
		//No more Hubsi
	}
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
	AnimationHandler();
}

//Sets the Animation for Walking, Idle and Jumping
void AInputController::AnimationHandler()
{
	PinguCharacter = Cast<APinguCharacter>(GetPawn());
	if (PinguCharacter == nullptr)
	{
		return;
	}
	if (!bIsJumping && bIsWalking)
	{
		PinguCharacter->SetWalkAnimation();
		UE_LOG(LogTemp, Warning, TEXT("WalkAnimation Jumping:%s Walking:%s"),
		       (bIsJumping) ? TEXT("true") : TEXT("false"), (bIsWalking) ? TEXT("true"):TEXT("false"));
	}
	if (!bIsJumping && !bIsWalking)
	{
		PinguCharacter->SetIdleAnimation();
		UE_LOG(LogTemp, Warning, TEXT("IdleAnimation Jumping:%s Walking:%s"),
		       (bIsJumping) ? TEXT("true") : TEXT("false"), (bIsWalking) ? TEXT("true") : TEXT("false"));
	}
}

void AInputController::PlayLevelTheme()
{
	if (!MusicComponent)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the Music does not exist!"));
		return;	
	}
	if (!MusicComponent->GetSound()) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("The Music MetaSound is not loaded into the Component, did you change its location in the project?"));
		return;
	}

	if (MusicComponent->IsActive() == false)
	{
		MusicComponent->SetActive(true);
	}
	if (MusicComponent->IsPlaying() == false)
	{
		MusicComponent->Play();
	}

	MusicComponent->SetTriggerParameter(*MUSIC_TRIGGER_NAME);
}

void AInputController::PauseLevelTheme()
{
	if (!MusicComponent) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the Music does not exist!"));
		return;	
	}
	if (!MusicComponent->GetSound())
	{
		UE_LOG(LogTemp, Fatal, TEXT("The Music MetaSound is not loaded into the Component, did you change its location in the project?"));
	}
	if (MusicComponent->IsActive() == false)
	{
		MusicComponent->SetActive(true);
	}
	if (MusicComponent->IsPlaying() == false)
	{
		MusicComponent->Play();
	}

	MusicComponent->SetTriggerParameter(*PAUSE_MUSIC_TRIGGER_NAME);
}

void AInputController::UnpauseLevelTheme()
{
	if (!MusicComponent) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the Music does not exist!"));
		return;	
	}
	if (!MusicComponent->GetSound())
	{
		UE_LOG(LogTemp, Fatal, TEXT("The Music MetaSound is not loaded into the Component, did you change its location in the project?"));
	}
	if (MusicComponent->IsActive() == false)
	{
		MusicComponent->SetActive(true);
	}
	if (MusicComponent->IsPlaying() == false)
	{
		MusicComponent->Play();
	}

	MusicComponent->SetTriggerParameter(*UNPAUSE_MUSIC_TRIGGER_NAME);
}

void AInputController::PlayUIConfirmSound()
{
	if (!UISFXComponent) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the UI Sounds does not exist!"));
		return;	
	}
	if (!UISFXComponent->GetSound())
	{
		UE_LOG(LogTemp, Fatal, TEXT("The UI MetaSound is not loaded into the Component, did you change its location in the project?"));
		return;
	}

	if (UISFXComponent->IsActive() == false) UISFXComponent->SetActive(true);
	if (UISFXComponent->IsPlaying() == false) UISFXComponent->Play();

	UISFXComponent->SetTriggerParameter(*UI_CONFIRM_TRIGGER_NAME);
}

void AInputController::PlayUIHoverSound()
{
	if (!UISFXComponent) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the UI Sounds does not exist!"));
		return;	
	}
	if (!UISFXComponent->GetSound())
	{
		UE_LOG(LogTemp, Fatal, TEXT("The UI MetaSound is not loaded into the Component, did you change its location in the project?"));
		return;
	}

	if (UISFXComponent->IsActive() == false) UISFXComponent->SetActive(true);
	if (UISFXComponent->IsPlaying() == false) UISFXComponent->Play();

	UISFXComponent->SetTriggerParameter(*UI_HOVER_TRIGGER_NAME);
}

void AInputController::PlayUIOpenSound()
{
	if (!UISFXComponent) 
	{
		UE_LOG(LogTemp, Fatal, TEXT("Audio Component for the UI Sounds does not exist!"));
		return;	
	}
	if (!UISFXComponent->GetSound())
	{
		UE_LOG(LogTemp, Fatal, TEXT("The UI MetaSound is not loaded into the Component, did you change its location in the project?"));
		return;
	}

	if (UISFXComponent->IsActive() == false) UISFXComponent->SetActive(true);
	if (UISFXComponent->IsPlaying() == false) UISFXComponent->Play();

	UISFXComponent->SetTriggerParameter(*UI_OPEN_TRIGGER_NAME);
}

void AInputController::OpenOptionsMenu()
{
	if (!OptionMenuObject)
	{
		UE_LOG(LogTemp, Error, TEXT("OptionMenu is not valid!"));
		return;
	}

	OptionMenu = CreateWidget<UOptionMenu>(this, OptionMenuObject, "Option Menu");

	if (OptionMenu)
	{
		OptionMenu->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OptionMenu is not valid!"));
	}
}
