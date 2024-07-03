// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

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

private:
	const FString IA_MOVE_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'");
	const FString PLAYER_CTX_PATH = TEXT("/Game/Input/IMC_Character");
	const FString IA_JUMP_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'");
	const FString IA_SLAP_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Slap.IA_Slap'");
	const FString IA_NOOT_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_NootNoot.IA_NootNoot'");
	const FString IMC_PATH = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Character.IMC_Character'");


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

#pragma endregion
};
