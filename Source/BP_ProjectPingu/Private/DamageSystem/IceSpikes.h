// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "IceSpikes.generated.h"

class ABossEnemy;
class ANormalEnemy;
class USphereComponent;

UCLASS()
class AIceSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceSpikes();

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/// <summary>When the IceSpike hits something this method will be called</summary>
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	const FString MESH_PATH = TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString MESH_NAME = FString(TEXT("Mesh"));
	const FString BOX_NAME = TEXT("Box Collision");
	const FString PROJECTILE_MOVEMENT_NAME = TEXT("Projectile Movement");

	/// <summary>Material Component of the Ice Spike</summary>
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Material", Category = "Components"))
	UMaterialInterface* Material = nullptr;

	/// <summary>Mesh Component of the Ice Spike</summary>
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh", Category = "Components"))
	UStaticMeshComponent* Mesh = nullptr;

	/// <summary>Projectile Movement Component of the Ice Spike</summary>
	UPROPERTY(EditAnywhere, DisplayName = "Projectile Movement", Category = "Components", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	/// <summary>The enemies that can be hit from the Ice Spike</summary>
	ANormalEnemy* Enemy = nullptr;
	ABossEnemy* BossEnemy = nullptr;

};
