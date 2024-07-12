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


	UPROPERTY(EditAnywhere, DisplayName = "Box Collision", Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxCollision = nullptr;
};
