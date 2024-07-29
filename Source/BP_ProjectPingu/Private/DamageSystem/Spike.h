// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spike.generated.h"

class UBoxComponent;

UCLASS()
class ASpike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpike();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString MESH_NAME = FString(TEXT("Mesh"));
	const FString MESH_PATH = FString(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Artist/Stephan/Spikes.Spikes'"));
	const FString MAT_PATH = FString(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	const FString BOX_COLLISION_NAME = FString(TEXT("Box Collision"));

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> Material = nullptr;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

};
