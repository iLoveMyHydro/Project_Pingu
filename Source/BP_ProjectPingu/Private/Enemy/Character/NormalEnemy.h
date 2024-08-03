// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "BP_ProjectPingu/Private/DamageSystem/Damagable.h"
#include "Components/SphereComponent.h"
#include "OilBarrel/OilBarrel.h"
#include "NormalEnemy.generated.h"

class ANormalAIController;
class FiniteStateMachineAI1;

UCLASS()
class ANormalEnemy : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANormalEnemy();

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

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	const FString MESH_PATH = FString(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
	const FString FSM_CONTROLLER_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.NormalAIController'"));
	const FString PLAYER_CLASS_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'"));
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString SPAWNLOCATION_OIL_BARREL_NAME = FString(TEXT("Ice Spike Spawn Location"));

	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Ice Spike", Category = "Attack")
	USceneComponent* SpawnLocationOilBarrel = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	UPROPERTY(EditAnywhere)
	USphereComponent* sphereColl = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Oil Barrel Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	TSubclassOf<AActor> PlayerClass;

	TObjectPtr<AOilBarrel> OilBarrel = nullptr;

	TObjectPtr<USceneComponent> SpawnPoint = nullptr;

	ANormalEnemy* Character = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 2;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	FiniteStateMachineAI1* Fsm = nullptr;

	APinguCharacter* PinguCharacter = nullptr;

	ANormalAIController* Controller = nullptr;
};
