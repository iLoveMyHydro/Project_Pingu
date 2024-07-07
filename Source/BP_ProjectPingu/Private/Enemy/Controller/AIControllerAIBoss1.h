// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerAIBoss1.generated.h"

class FiniteStateMachineAIBoss1;

/**
 * 
 */
UCLASS()
class AAIControllerAIBoss1 : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetPlayer(void) const { return Player; }
	class AAIBossEnemy1* GetCharacterAI(void) const { return Character; };

	void SetCharacter(class AAIBossEnemy1* A_Character) { Character = A_Character; }

private:
	FiniteStateMachineAIBoss1* Fsm = nullptr;
	AActor* Player = nullptr;
	class AAIBossEnemy1* Character = nullptr;
};
