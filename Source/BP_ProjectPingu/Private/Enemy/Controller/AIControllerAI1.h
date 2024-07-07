// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerAI1.generated.h"

class FiniteStateMachineAI1;

/**
 * 
 */
UCLASS()
class AAIControllerAI1 : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetPlayer(void) const { return Player; }
	class AAIEnemy1* GetCharacterAI(void) const { return Character; };

	void SetCharacter(class AAIEnemy1* A_Character) { Character = A_Character; }

private:
	FiniteStateMachineAI1* fsm = nullptr;
	AActor* Player = nullptr;
	class AAIEnemy1* Character = nullptr;
};
