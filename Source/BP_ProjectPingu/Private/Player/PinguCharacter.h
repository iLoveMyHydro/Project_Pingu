// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DamageSystem/Damagable.h"
#include "DamageSystem/IceSpikes.h"
#include "GameFramework/Character.h"
#include "PinguCharacter.generated.h"


class UPlayerHUD;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UDeathScreen;


UCLASS()
class APinguCharacter : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APinguCharacter();

	// Applies the Damage to the Player
	virtual void ApplyDamage(int A_DamageAmount) override;

	// Return bool if colliding
	bool GetIsColliding();

	// Get Other Character
	ACharacter* GetOtherCharacter();

	// Get IceSpike Value
	int GetIceSpikes();

	// Set Ice Spike Value
	void SetIceSpikes(int A_IceSpikes);

	// Throw Ice Spike
	void ThrowIceSpikes();

	// Get Info if got Ice Spike
	bool GetGotIceSpikes();

	// Respawn Player
	void Respawn();

private:
	// Initialize Camera
	auto InitCamera(void) -> class UCameraComponent*;

	// Initialize Player Values
	void InitPlayer(void);

	// Box Begin Overlap
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Camera Component
	FORCEINLINE class UCameraComponent* Get2DCameraComponent() const { return PinguCameraComponent; }

	// Spring Arm
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString MESH_PATH = FString(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	const FString MAT_PATH = FString(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	const FString MESH_ICE_SPIKE_PATH = FString(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	const FString MAT_ICE_SPIKE_PATH = FString(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	const FString ANIM_PATH = FString(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/Player/BP_AnimInstance.BP_AnimInstance_C'"));
	const FString PLAYER_HUD_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code'"));
	const FString DEATH_SCREEN_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_DeathScreen'"));

	const FString STIMULI_NAME = FString(TEXT("Stimuli"));
	const FString MESH_NAME = FString(TEXT("Mesh"));
	const FString CAMERA_NAME = FString(TEXT("Camera"));
	const FString CAMERA_ARM_NAME = FString(TEXT("CameraBoom"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
	const FString FEET_COLLISION_NAME = FString(TEXT("Feet Collision"));
	const FString SCENE_ROOT_NAME = FString(TEXT("Scene Root"));
	const FString SPAWNLOCATION_ICE_SPIKE_NAME = FString(TEXT("Ice Spike Spawn Location"));
	const FString ICE_SPIKE_PATH = FString(TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.IceSpikes'"));
	const FString IDLE_ANIM_PATH = FString(TEXT("AnimSequence'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Idle_Anim'"));
	const FString WALK_ANIM_PATH = FString(TEXT("AnimSequence'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Walk_Anim'"));
	const FString SLAP_ANIM_PATH = FString(TEXT("AnimSequence'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Bitch_Slap_Anim'"));
	const FString NOOT_ANIM_PATH = FString(TEXT("AnimSequence'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Noot_Noot_Anim'"));
	const FString JUMP_ANIM_PATH = FString(TEXT("AnimSequence'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Jump1_Anim'"));

	//Audio Stuff (Coded by Hubsi)
	const FString ATTACK_SFX_NAME = FString(TEXT("AttackSFX"));
	const FString DAMAGE_SFX_NAME = FString(TEXT("DamageSFX"));
	const FString FOOTSTEPS_SFX_NAME = FString(TEXT("FootstepSFX"));
	const FString JUMP_SFX_NAME = FString(TEXT("JumpSFX"));

	const FString ATTACK_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Attack.META_Attack'"));
	const FString DAMAGE_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Damage.META_Damage'"));
	const FString FOOTSTEPS_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Footsteps.META_Footsteps'"));
	const FString JUMP_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Jump.META_Jump'"));

	const FString MELEE_ATTACK_TRIGGER_NAME = FString(TEXT("PlayMeleeAttack"));
	const FString RANGED_ATTACK_TRIGGER_NAME = FString(TEXT("PlayRangedAttack"));
	const FString DAMAGE_TRIGGER_NAME = FString(TEXT("PlayDamage"));
	const FString FOOTSTEP_TRIGGER_NAME = FString(TEXT("PlayFootstep"));
	const FString JUMP_TRIGGER_NAME = FString(TEXT("Jump"));
	//Audio Stuff End

	UPROPERTY(EditAnywhere, DisplayName = "Spawn Location", Category = "Respawn")
	FVector SpawnLocation = FVector(-7250.548968, -3290.544749, 420.834087);

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 1;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditAnywhere, DisplayName = "Other Characters", Category = "Other Character", meta = (AllowPrivateAccess = true))
	ACharacter* OtherCharacter = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	UPROPERTY(EditAnywhere, DisplayName = "Max Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int MaxHealth = 3;

	UPROPERTY(EditAnywhere, DisplayName = "Is Colliding", Category = "Attack", meta = (AllowPrivateAccess = true))
	bool IsColliding = false;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "FeetCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionFeet = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Material", Category = "Components", meta = (AllowPrivateAccess = true))
	UMaterial* Material = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Camera", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UCameraComponent> PinguCameraComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "CameraArm", Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<class USpringArmComponent> CameraBoom = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spikes", Category = "Attack", meta = (AllowPrivateAccess = true))
	int IceSpikes = 0;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spikes Max", Category = "Attack", meta = (AllowPrivateAccess = true))
	int IceSpikesMax = 5;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spike Speed", Category = "Attack", meta = (AllowPrivateAccess = true))
	int IceSpikeSpeed = 5;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spike Actor", Category = "Attack", meta = (AllowPrivateAccess = true));
	TSubclassOf<class AIceSpikes> IceSpikeProjectile;

	UPROPERTY(EditAnywhere, DisplayName = "Ice Spike Offset", Category = "Attack", meta = (AllowPrivateAccess = true))
	FVector MuzzleOffset;

	APinguCharacter* Character = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Ice Spike", Category = "Attack")
	USceneComponent* SpawnLocationIceSpike = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Got IceSpikes", Category = "Attack")
	bool bGotIceSpikes = false;
};
