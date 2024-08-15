// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "DamageSystem/Damagable.h"
#include "Enemy/Character/NormalEnemy.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

class ABossEnemy;
class APinguCharacter;
/**
 * 
 */
UCLASS()
class AInputController : public APlayerController
{
	GENERATED_BODY()

public:
	AInputController();

	//Audio Stuff Begin
	void PlayLevelTheme();
	void PauseLevelTheme();
	void UnpauseLevelTheme();
	void PlayUIConfirmSound();
	void PlayUIHoverSound();
	void PlayUIOpenSound();
	//Audio Stuff End

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	void InitInputAction(void);

	void Tick(float DeltaSeconds) override;

	void Move(const FInputActionValue& Value);
	void Jump(void);
	void StopJump(void);
	void HandleStopMovement(const FInputActionValue& Value);
	void HandleSlapAttack(void);
	void HandleNootAttack(void);
	void HandleSlapAttackComplete(void);
	void HandlePauseAction(void);
	void HandleStartedMovement();
	void AnimationHandler(void);

private:
	const FString PLAYER_CTX_PATH = TEXT("/Game/Input/IMC_Character");
	const FString IA_MOVE_PATH = TEXT("/Game/Input/Actions/IA_Move");
	const FString IA_JUMP_PATH = TEXT("/Game/Input/Actions/IA_Jump");
	const FString IA_SLAP_PATH = TEXT("/Game/Input/Actions/IA_Slap");
	const FString IA_NOOT_PATH = TEXT("/Game/Input/Actions/IA_NootNoot");
	const FString IMC_PATH = TEXT("/Game/Input/IMC_Character");
	const FString IA_PAUSE_PATH = TEXT("/Game/Input/Actions/IA_Pause");
	const FString PAUSE_MENU_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_PauseMenu_Code"));
	const FString PLAYER_HUD_PATH = FString(TEXT("/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code"));

	//Audio Stuff by Hubsi
	const FString MUSIC_PATH = FString(TEXT("/Game/Audio/MetaSounds/META_Music"));
	const FString MUSIC_NAME = FString(TEXT("Music"));
	const FString MUSIC_TRIGGER_NAME = FString(TEXT("PlayLevelTheme"));
	const FString PAUSE_MUSIC_TRIGGER_NAME = FString(TEXT("PauseLevelTheme"));
	const FString UNPAUSE_MUSIC_TRIGGER_NAME = FString(TEXT("UnpauseLevelTheme"));
	const FString UI_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_UI.META_UI'"));
	const FString UI_NAME = FString(TEXT("UI SFX"));
	const FString UI_CONFIRM_TRIGGER_NAME = FString(TEXT("UIConfirm"));
	const FString UI_HOVER_TRIGGER_NAME = FString(TEXT("UIHover"));
	const FString UI_OPEN_TRIGGER_NAME = FString(TEXT("UIOpen"));

	UPROPERTY(VisibleAnywhere, DisplayName = "Music", Category = "Components")
	TObjectPtr<class UAudioComponent> MusicComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "UI SFX", Category = "Components")
	TObjectPtr<class UAudioComponent> UISFXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "Audio Component Auto Activation", Category = "Components")
	bool bAutoActivate = false;

	UPROPERTY(EditAnywhere, DisplayName = "Walking State", Category = "AnimationHandler")
	bool bIsWalking = false;

	UPROPERTY(EditAnywhere, DisplayName = "Jump State", Category = "AnimationHandler")
	bool bIsJumping = false;

	UPROPERTY(EditAnywhere)
	class AActor* SelectedActor;


#pragma region Attack

	UPROPERTY(EditAnywhere, DisplayName = "Is Attacking", Category = "Attack", meta = (AllowPrivateAccess = true))
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, DisplayName = "Damage", Category = "Attack", meta = (AllowPrivateAccess = true))
	float Damage = 1;

#pragma endregion


#pragma region Movement

	UPROPERTY(EditAnywhere, DisplayName = "Speed", Category = "Movement", meta = (AllowPrivateAccess = true))
	int32 Speed = 1;

	UPROPERTY(EditAnywhere, DisplayName = "Direction", Category = "Movement", meta = (AllowPrivateAccess = true))
	FVector Dir = FVector::Zero();



#pragma  endregion

#pragma region InputAction

	UPROPERTY(EditAnywhere, DisplayName = "MappingContext", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "MoveRight", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Jump", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputAction* JumpAction = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Slap", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputAction* SlapAction = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Noot Noot", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputAction* NootNootAction = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Pause Action", Category = "InputAction", meta = (AllowPrivateAccess = true))
	UInputAction* PauseAction = nullptr;

#pragma endregion

	APinguCharacter* PinguCharacter = nullptr;
	ANormalEnemy* Enemy = nullptr;
	ABossEnemy* BossEnemy = nullptr;

	UPROPERTY()
	class UPauseMenu* PauseMenu = nullptr;

	UPROPERTY()
	TSubclassOf<class UPauseMenu> PauseMenuObject;

	UPROPERTY()
	class UPlayerHUD* PlayerHUD = nullptr;

	UPROPERTY()
	TSubclassOf<class UPlayerHUD> PlayerHUDObject;

	UPROPERTY()
	float SlapCoolDown = 0;

	const float SlapCoolDownTime = 1;

};
