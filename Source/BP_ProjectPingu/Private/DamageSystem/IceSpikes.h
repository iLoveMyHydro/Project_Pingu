// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "IceSpikes.generated.h"

class AAIEnemy1;
class AAIBossEnemy1;

UCLASS()
class AIceSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceSpikes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	
	const FString MESH_PATH = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");
	const FString BOX_NAME = TEXT("Box Collision");
	const FString PROJECTILE_MOVEMENT_NAME = TEXT("Projectile Movement");

	UPROPERTY(EditAnywhere, DisplayName = "Mesh", Category = "Components", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Box Collision", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Projectile Movement", Category = "Components", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	AAIBossEnemy1* BossEnemy = nullptr;
	AAIEnemy1* Enemy = nullptr;

};
