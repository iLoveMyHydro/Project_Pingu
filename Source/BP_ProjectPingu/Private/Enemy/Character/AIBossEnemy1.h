// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "AIBossEnemy1.generated.h"

UCLASS()
class AAIBossEnemy1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBossEnemy1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	const FString MESH_PATH = TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'");
	const FString FSM_CONTROLLER_PATH = TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.AIControllerAI1'");
	const FString PLAYER_CLASS_PATH = TEXT("/Script/CoreUObject.Class'/Script/BP_ProjectPingu.PinguCharacter'");
	const FString BOX_COLLISION_NAME = TEXT("Box Collision");

	UPROPERTY(EditAnywhere, DisplayName = "Health", Category = "Value", meta = (AllowPrivateAccess = true))
	int Health = 3;

	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	TSubclassOf<AActor> playerClass;
};
