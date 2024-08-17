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

	// Applies the Damage to the Boss Enemy
	virtual void ApplyDamage(int A_DamageAmount) override;

	// Spawns the Oil Barrel 
	void ThrowOilBarrel();

	void ThrowOilBarrelFast();

	// When the Boss Enemy gets hit by the Ice Spikes 
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the Player exits the Sphere
	UFUNCTION()
	void OnCollisionExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Audio Functions
	void PlayBossDamageSFX();
	// less Audio Functions from here

	// Sets the animation for the Boss Enemy
	ABossEnemy& SetIdleAnimation(void);
	ABossEnemy& SetThrowAnimation(void);

private:
	const FString MESH_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Idle"));
	const FString MATERIAL_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/Material/MAT_Enemy"));
	const FString FSM_CONTROLLER_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.BossAIController'"));
	const FString PLAYER_CLASS_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'"));
	const FString OIL_BARREL_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.OilBarrel'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString SPAWNLOCATION_OIL_BARREL_NAME = FString(TEXT("Oil Barrel Spawn Location"));
	const FString IDLE_ANIM_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Idle_Anim"));
	const FString THROW_ANIM_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/Enemy/FBX/Scientist_Throw_Anim"));
	const FName MAIN_MENU_LEVEL = FName(TEXT("/Game/Maps/MainMenu_Code"));


	// this audio section has been brought to you by Hubsi (Für Marcus: Hubsi == Alex Huber)
	const FString BOSS_DAMAGE_SFX_COMPONENT_NAME = FString(TEXT("BossDamageSFX"));
	
	const FString BOSS_DAMAGE_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_BossDamage.META_BossDamage'"));

	const FString BOSS_DAMAGE_SFX_TRIGGER_NAME = FString(TEXT("BossDamage"));
	// end of this audio section

	// Spawn Location for the Oil Barrel
	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Oil Barrel", Category = "Attack")
	USceneComponent* SpawnLocationOilBarrel = nullptr;

	// Health Amount for the Boss Enemy
	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 6;

	// Player that can get and set damage
	APinguCharacter* PinguCharacter = nullptr;

	// Respawn Delay of the Oil Barrel (normal Version)
	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 1.75;

	// Respawn Delay of the Oil Barrel (fast Version)
	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelayFast = 1.5;

	// Timer Handler for normal Version
	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	// Timer Handler for fast Version
	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle Three", Category = "Respawn")
	FTimerHandle RespawnTimerHandleFast;

	// Sphere Collider for the Boss Enemy
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereColl = nullptr;

	// Box Collider for the Boss Enemy
	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	// Projectile of the Oil Barrel
	UPROPERTY(EditAnywhere, DisplayName = "Oil Barrel Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AOilBarrel> OilBarrelProjectile;

	// Idle Animation
	UPROPERTY(EditAnywhere, DisplayName = "Animation Idle", Category = "Animation")
	UAnimSequence* IdleAnim = nullptr;

	// Throw Animation
	UPROPERTY(EditAnywhere, DisplayName = "Animation Throw", Category = "Animation")
	UAnimSequence* ThrowAnim = nullptr;

	// Material for the Boss Enemy
	UPROPERTY(EditAnywhere, DisplayName = "Material", Category = "Components")
	UMaterial* Material = nullptr;

	// More Audio
	UPROPERTY(EditAnywhere, DisplayName = "BossDamageSFX", Category = "Components")
	TObjectPtr<UAudioComponent> BossDamageSFXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "Audio Component Auto Activation", Category = "Components")
	bool bAutoActivate = false;
	// Less Audio

	// Oil Barrel to spawn
	TObjectPtr<AOilBarrel> OilBarrel = nullptr;

	// Character of the Boss Enemy
	ABossEnemy* Character = nullptr;

	// FSM for the Boss Enemy
	NormalFSM* Fsm = nullptr;

	// PlayerController from the PinguCharacter
	AInputController* PlayerController = nullptr;

	// BossController
	ABossAIController* Controller = nullptr;
};
