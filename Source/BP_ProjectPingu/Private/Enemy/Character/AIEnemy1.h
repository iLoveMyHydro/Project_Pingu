// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "BP_ProjectPingu/Private/DamageSystem/Damagable.h"
#include "OilBarrel/OilBarrel.h"
#include "AIEnemy1.generated.h"

UCLASS()
class AAIEnemy1 : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemy1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ApplyDamage(int A_DamageAmount) override;

	void ThrowOilBarrel();

private:
	const FString MESH_PATH = FString(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	const FString FSM_CONTROLLER_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.AIControllerAI1'"));
	const FString PLAYER_CLASS_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'"));
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString ENEMY_NAME = FString(TEXT("AI Enemy"));
	const FString SPAWNLOCATION_OIL_BARREL_NAME = FString(TEXT("Ice Spike Spawn Location"));

	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Ice Spike", Category = "Attack")
	USceneComponent* SpawnLocationIceSpike = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spike Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	TSubclassOf<AActor> PlayerClass;

	TObjectPtr<AOilBarrel> OilBarrel = nullptr;

	TObjectPtr<USceneComponent> SpawnPoint = nullptr;

	AAIEnemy1* Character = nullptr;
};
