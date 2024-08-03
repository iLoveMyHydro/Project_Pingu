// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "IceSpikes.generated.h"

class ANormalEnemy;
class USphereComponent;

UCLASS()
class AIceSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceSpikes();

	///** Returns CollisionComp subobject **/
	//USphereComponent* GetCollisionComp() const { return Sphere; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	
	const FString MESH_PATH = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString BOX_NAME = TEXT("Box Collision");
	const FString PROJECTILE_MOVEMENT_NAME = TEXT("Projectile Movement");

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Material", Category = "Components"))
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh", Category = "Components"))
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Projectile Movement", Category = "Components", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	ANormalEnemy* Enemy = nullptr;

};
