// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "DamageSystem/Damagable.h"
#include "Enemy/Character/AIBossEnemy1.h"
#include "Enemy/Character/AIEnemy1.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

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

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	void InitInputAction(void);

	void Move(const FInputActionValue& Value);
	void Jump(void);
	void StopJump(void);
	void HandleStopMovement(const FInputActionValue& Value);
	void HandleSlapAttack(void);
	void HandleNootAttack(void);
	void HandleSlapAttackComplete(void);
	void HandlePauseAction(void);
	void HandleStartedMovement();

private:
	const FString IA_MOVE_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'");
	const FString PLAYER_CTX_PATH = TEXT("/Game/Input/IMC_Character");
	const FString IA_JUMP_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'");
	const FString IA_SLAP_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Slap.IA_Slap'");
	const FString IA_NOOT_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_NootNoot.IA_NootNoot'");
	const FString IMC_PATH = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Character.IMC_Character'");
	const FString IA_PAUSE_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Pause.IA_Pause'");
	const FString PAUSE_MENU_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PauseMenu_Code.WBP_PauseMenu_Code'"));
	const FString PLAYER_HUD_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code'"));


	UPROPERTY(EditAnywhere)
	class AActor* SelectedActor;


#pragma region Attack

	UPROPERTY(EditAnywhere, DisplayName = "Is Attacking", Category = "Attack", meta = (AllowPrivateAccess = true))
	bool IsAttacking = false;

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
	AAIBossEnemy1* BossEnemy = nullptr;
	AAIEnemy1* Enemy = nullptr;

	UPROPERTY()
	class UPauseMenu* PauseMenu = nullptr;

	UPROPERTY()
	TSubclassOf<class UPauseMenu> PauseMenuObject;

	UPROPERTY()
	class UPlayerHUD* PlayerHUD = nullptr;

	UPROPERTY()
	TSubclassOf<class UPlayerHUD> PlayerHUDObject;
};
