// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DamageSystem/Damagable.h"
#include "GameFramework/Character.h"
#include "PinguCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class APinguCharacter : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APinguCharacter();

	virtual void ApplyDamage(int A_DamageAmount) override;

private:
	auto InitCamera(void) -> class UCameraComponent*;

	void InitPlayer(void);

	FORCEINLINE class UCameraComponent* Get2DCameraComponent() const { return PinguCameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	const FString MESH_PATH = TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString CAMERA_NAME = TEXT("Camera");
	const FString CAMERA_ARM_NAME = TEXT("CameraBoom");
	const FString BOX_COLLISION_NAME = TEXT("Box Collision");
	const FString SCENE_ROOT_NAME = TEXT("Scene Root");


	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	TObjectPtr<USceneComponent> SceneRoot = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Material", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInterface> Material = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Camera", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> PinguCameraComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "CameraArm", Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<class USpringArmComponent> CameraBoom = nullptr;
};
