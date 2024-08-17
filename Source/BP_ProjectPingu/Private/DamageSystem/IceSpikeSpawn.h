// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "IceSpikeSpawn.generated.h"

UCLASS()
class AIceSpikeSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceSpikeSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString BOX_NAME = TEXT("Box Collision");
	const FString MESH_NAME = FString(TEXT("Mesh"));
	const FString MESH_PATH = FString(TEXT("/Game/Assets/Artist/Jean-Marc/IceSpike/IceSpike"));
	const FString MAT_PATH = FString(TEXT("/Game/IcePropsContent/Materials/M_Ice_Main"));

	/// <summary>Box Collision for the Spawner</summary>
	UPROPERTY(EditAnywhere, DisplayName = "Box Collision", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxCollision = nullptr;

	/// <summary> Material for the Spawner</summary>
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> Material = nullptr;

	/// <summary>Mesh for the Spawner</summary>
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Mesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;


};
