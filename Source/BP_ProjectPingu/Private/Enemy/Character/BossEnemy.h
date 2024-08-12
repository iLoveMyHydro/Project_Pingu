// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "DamageSystem/Damagable.h"
#include "Components/SphereComponent.h"
#include "OilBarrel/OilBarrel.h"
#include "BossEnemy.generated.h"

class ABossAIController;
class NormalFSM;
class AInputController;

UCLASS()
class ABossEnemy : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossEnemy();

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

	void ThrowThreeOilBarel();

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Audio Functions
	void PlayBossDamageSFX();
	//less Audio Functions from here

	const FString MESH_PATH = FString(TEXT("/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh"));
	const FString FSM_CONTROLLER_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.BossAIController'"));
	const FString PLAYER_CLASS_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'"));
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString SPAWNLOCATION_OIL_BARREL_NAME = FString(TEXT("Oil Barrel Spawn Location"));

	//this audio section has been brought to you by Hubsi (Für Marcus: Hubsi == Alex Huber)
	const FString BOSS_DAMAGE_SFX_COMPONENT_NAME = FString(TEXT("BossDamageSFX"));
	
	const FString BOSS_DAMAGE_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_BossDamage.META_BossDamage'"));

	const FString BOSS_DAMAGE_SFX_TRIGGER_NAME = FString(TEXT("BossDamage"));
	//end of this audio section

	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Oil Barrel", Category = "Attack")
	USceneComponent* SpawnLocationOilBarrel = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 6;

	APinguCharacter* PinguCharacter = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 3;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelayFast = 1;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle Three", Category = "Respawn")
	FTimerHandle RespawnTimerHandleThree;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereColl = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Oil Barrel Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	//More Audio
	UPROPERTY(EditAnywhere, DisplayName = "BossDamageSFX", Category = "Components")
	TObjectPtr<UAudioComponent> BossDamageSFXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "Audio Component Auto Activation", Category = "Components")
	bool bAutoActivate = false;
	//Less Audio

	TSubclassOf<AActor> PlayerClass;

	TObjectPtr<AOilBarrel> OilBarrel = nullptr;

	ABossEnemy* Character = nullptr;

	NormalFSM* Fsm = nullptr;

	AInputController* PlayerController = nullptr;

	ABossAIController* Controller = nullptr;
};
