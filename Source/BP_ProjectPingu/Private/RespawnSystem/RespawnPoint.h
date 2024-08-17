// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameModeBase/GameModeBaseCode.h"
#include "Player/InputController.h"
#include "Player/PinguCharacter.h"
#include "RespawnPoint.generated.h"

UCLASS()
class ARespawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARespawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// On Box Begin Overlap
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	const FString ARROW_NAME = TEXT("Arrow");
	const FString BOX_COLLISION_NAME = TEXT("Box Collision");


	UPROPERTY(EditAnywhere, DisplayName = "BoxCollider", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "Arrow", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UArrowComponent> ArrowComponent = nullptr;

	UPROPERTY(EditAnywhere, DisplayName = "b Spawn Point", Category = "Component")
	bool bSpawnPointSet = false;

	APinguCharacter* Character = nullptr;

	AGameModeBaseCode* GameMode = nullptr;

	AInputController* InputController = nullptr;
};
