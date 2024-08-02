// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "DamageSystem/Damagable.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "GameFramework/Character.h"
#include "AIBossEnemy1.generated.h"

UCLASS()
class AAIBossEnemy1 : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBossEnemy1();

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
	const FString MESH_PATH = TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'");
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString FSM_CONTROLLER_PATH = TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.AIControllerAI1'");
	const FString PLAYER_CLASS_PATH = TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'");
	const FString BOX_COLLISION_NAME = TEXT("Box Collision");

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	UPROPERTY(EditAnywhere)
	USphereComponent* sphereColl = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Oil Barrel Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 2;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	TSubclassOf<AActor> playerClass;

	FiniteStateMachineAI1* Fsm = nullptr;

	AAIBossEnemy1* Character = nullptr;

};
