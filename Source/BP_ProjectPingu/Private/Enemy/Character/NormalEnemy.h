// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "DamageSystem/Damagable.h"
#include "Components/SphereComponent.h"
#include "OilBarrel/OilBarrel.h"
#include "NormalEnemy.generated.h"

class NormalFSM;
class ANormalAIController;
class AInputController;

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

	// Applies the Damage to the Normal Enemy
	virtual void ApplyDamage(int A_DamageAmount) override;

	// Spawns the Oil Barrel 
	void ThrowOilBarrel();

	// When the Normal Enemy gets hit by the Ice Spikes or the Slap Attack 
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the Player exits the Sphere
	UFUNCTION()
	void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Audio Functions
	void PlayEnemyDamageSFX();
	// less Audio Functions from here

	// Animations for the Normal Enemy
	ANormalEnemy& SetIdleAnimation(void);
	ANormalEnemy& SetThrowAnimation(void);

private:
	const FString MESH_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Idle"));
	const FString MATERIAL_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/Material/MAT_Enemy"));
	const FString FSM_CONTROLLER_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.NormalAIController'"));
	const FString PLAYER_CLASS_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'"));
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString SPAWNLOCATION_OIL_BARREL_NAME = FString(TEXT("Oil Barrel Spawn Location"));
	const FString IDLE_ANIM_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Idle_Anim"));
	const FString THROW_ANIM_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Throw_Anim"));

	// this audio section has been brought to you by Hubsi (Für Marcus: Hubsi == Alex Huber)
	const FString ENEMY_DAMAGE_SFX_COMPONENT_NAME = FString(TEXT("EnemyDamageSFX"));
	
	const FString ENEMY_DAMAGE_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_EnemyDamage.META_EnemyDamage'"));

	const FString ENEMY_DAMAGE_SFX_TRIGGER_NAME = FString(TEXT("EnemyDamage"));
	// end of this audio section

	// Spawn Location for the Oil Barrel
	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Oil Barrel", Category = "Attack")
	USceneComponent* SpawnLocationOilBarrel = nullptr;

	// Health Amount for the Normal Enemy
	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	// Sphere Collider for the Normal Enemy
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereColl = nullptr;

	// Box Collider for the Normal Enemy
	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	// Projectile of the Oil Barrel
	UPROPERTY(EditAnywhere, DisplayName = "Oil Barrel Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	// Oil Barrel to spawn
	TObjectPtr<AOilBarrel> OilBarrel = nullptr;

	// Character of the Normal Enemy
	ANormalEnemy* Character = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 1.75f;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	//More Audio
	UPROPERTY(EditAnywhere, DisplayName = "EnemyDamageSFX", Category = "Components")
	TObjectPtr<UAudioComponent> EnemyDamageSFXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "Audio Component Auto Activation", Category = "Components")
	bool bAutoActivate = false;
	//Less Audio

	UPROPERTY(EditAnywhere, DisplayName = "Animation Idle", Category = "Animation")
	UAnimSequence* IdleAnim = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Throw", Category = "Animation")
	UAnimSequence* ThrowAnim = nullptr;

	// FSM for the Normal Enemy
	NormalFSM* Fsm = nullptr;

	// BossController
	ANormalAIController* Controller = nullptr;

	// Controller of the PinguCharacter
	AInputController* PlayerController = nullptr;

	// Material of the Normal Enemy
	UPROPERTY(EditAnywhere, DisplayName = "Material", Category = "Components")
	UMaterial* Material = nullptr;
};
