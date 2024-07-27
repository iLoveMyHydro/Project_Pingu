// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject3Projectile.generated.h"

class UBoxComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AMyProject3Projectile : public AActor
{
	GENERATED_BODY()

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AMyProject3Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	UBoxComponent* GetCollisionComp() const { return BoxCollision; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	const FString MESH_PATH = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString BOX_NAME = TEXT("Box Collision");
	const FString PROJECTILE_MOVEMENT_NAME = TEXT("Projectile Movement");

	UPROPERTY(EditAnywhere, DisplayName = "Mesh", Category = "Components", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Box Collision", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxCollision = nullptr;
};

