// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PinguCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class APinguCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APinguCharacter();

private:
	auto InitCamera(void) -> class UCameraComponent*;
	void InitInputAction(void);

	void HandleRightMovement(const FInputActionValue& Ctx);
	void HandleStopMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	const FString MESH_PATH = TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString CAMERA_NAME = TEXT("Camera");
	const FString IA_MOVE_RIGHT_PATH = TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_MoveRight.IA_MoveRight'");
	const FString PLAYER_CTX_PATH = TEXT("/Game/Input/IMC_Character");

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> Material = nullptr;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Camera", Category = "Components"))
	TObjectPtr<class UCameraComponent> Cam = nullptr;

#pragma region Movement

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Speed", Category = "Movement"))
	int32 Speed = 1000;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Direction", Category = "Movement"))
	FVector Dir = FVector::Zero();

#pragma  endregion

#pragma region InputAction
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Context", Category = "InputAction"))
	UInputMappingContext* InputCtx = nullptr;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MoveRight", Category = "InputAction"))
	UInputAction* MoveActionRight = nullptr;


#pragma endregion

};
