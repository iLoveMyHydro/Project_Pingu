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


UCLASS()
class APinguCharacter : public ACharacter, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APinguCharacter();

	virtual void ApplyDamage(int A_DamageAmount) override;

	bool GetIsColliding();

	ACharacter* GetOtherCharacter();

	int GetIceSpikes();

	void SetIceSpikes(int A_IceSpikes);

	void ThrowIceSpikes();

	bool GetGotIceSpikes();

	APinguCharacter& SetIdleAnimation(void);
	APinguCharacter& SetNootAnimation(void);
	APinguCharacter& SetWalkAnimation(void);
	APinguCharacter& SetJumpAnimation(void);
	APinguCharacter& SetSlapAnimation(void);

	void Respawn();

	//Audio methods from Hubsi
	void PlaySlapSound();
	void PlayNootNootSound();
	void PlayDamageSound();
	void PlayFootstepSound();

private:
	auto InitCamera(void) -> class UCameraComponent*;

	void InitPlayer(void);

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE class UCameraComponent* Get2DCameraComponent() const { return PinguCameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString MESH_PATH = FString(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Artist/Jean-Marc/Character/FBX/Pinguin_Idle.Pinguin_Idle'"));
	const FString MAT_PATH = FString(TEXT("/Script/Engine.Material'/Game/Assets/Artist/Jean-Marc/Character/Material/MAT_Pingu.MAT_Pingu'"));
	const FString MESH_ICE_SPIKE_PATH = FString(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	const FString MAT_ICE_SPIKE_PATH = FString(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	const FString ANIM_PATH = FString(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/Player/BP_AnimInstance.BP_AnimInstance_C'"));
	const FString PLAYER_HUD_PATH = FString(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/HUD/C++/WBP_PlayerHUD_Code'"));

	const FString STIMULI_NAME = FString(TEXT("Stimuli"));
	const FString MESH_NAME = FString(TEXT("Mesh"));
	const FString CAMERA_NAME = FString(TEXT("Camera"));
	const FString CAMERA_ARM_NAME = FString(TEXT("CameraBoom"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));
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
	const FString ATTACK_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Attack.META_Attack'"));
	const FString DAMAGE_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Damage.META_Damage'"));
	const FString FOOTSTEPS_SFX_PATH = FString(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/Audio/MetaSounds/META_Footsteps.META_Footsteps'"));

	const FString MELEE_ATTACK_TRIGGER_NAME = FString(TEXT("PlayMeleeAttack"));
	const FString RANGED_ATTACK_TRIGGER_NAME = FString(TEXT("PlayRangedAttack"));
	const FString DAMAGE_TRIGGER_NAME = FString(TEXT("PlayDamage"));
	const FString FOOTSTEP_TRIGGER_NAME = FString(TEXT("PlayFootstep"));
	//Audio Stuff End

	UPROPERTY(EditAnywhere, DisplayName = "Spawn Location", Category = "Respawn")
	FVector SpawnLocation = FVector(-7250.548968, -3290.544749, 420.834087);

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 2;

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

	UPROPERTY()
	class UPlayerHUD* PlayerHUD = nullptr;

	UPROPERTY()
	TSubclassOf<class UPlayerHUD> PlayerHUDObject;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Idle", Category = "Animation")
	UAnimSequence* IdleAnim;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Walk", Category = "Animation")
	UAnimSequence* WalkAnim;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Noot", Category = "Animation")
	UAnimSequence* NootAnim;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Jump", Category = "Animation")
	UAnimSequence* JumpAnim;

	UPROPERTY(EditAnywhere, DisplayName = "Animation Slap", Category = "Animation")
	UAnimSequence* SlapAnim;

	UPROPERTY(EditAnywhere, DisplayName = "Spawnlocation Ice Spike", Category = "Attack")
	USceneComponent* SpawnLocationIceSpike = nullptr;

	//More Audio Stuff (by Hubsi)
	UPROPERTY(EditAnywhere, DisplayName = "Attack SFX", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAudioComponent> AttackSFXComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Damage SFX", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAudioComponent> DamageSFXComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Footstep SFX", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAudioComponent> FootstepSFXComponent = nullptr;

	UPROPERTY(VisibleAnywhere, DisplayName = "Audio Component Auto Activation", Category = "Components")
	bool bAutoActivate = false;

	UPROPERTY(EditAnywhere, DisplayName = "Got IceSpikes", Category = "Attack")
	bool bGotIceSpikes = false;

	// UPROPERTY(EditAnywhere, DisplayName = "Attack Sound", Category = "Audio")
	// class UMetaSoundSource* AttackSFX;

	// UPROPERTY(EditAnywhere, DisplayName = "Damage Sound", Category = "Audio")
	// class UMetaSoundSource* DamageSFX;

	// UPROPERTY(EditAnywhere, DisplayName = "Footstep Sound", Category = "Audio")
	// class UMetaSoundSource* FootstepSFX;
};
