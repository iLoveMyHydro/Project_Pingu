// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OilBarrel.generated.h"

UCLASS()
class AOilBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOilBarrel();

	void Throw(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	const FString MESH_PATH = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'");
	const FString MAT_PATH = TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");


	UPROPERTY(EditAnywhere, DisplayName = "Speed", Category = "Value", meta = (AllowPrivateAccess = true))
	int Speed = 100;

	UPROPERTY(EditAnywhere, DisplayName = "LowSpeed", Category = "Value", meta = (AllowPrivateAccess = true))
	int LowSpeed = 25;

};
