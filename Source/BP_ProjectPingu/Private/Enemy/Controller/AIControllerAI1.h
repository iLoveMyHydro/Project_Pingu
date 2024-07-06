// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAI1.h"
#include "AIControllerAI1.generated.h"

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
	void virtual Initialize();

	AActor* GetPlayer(void) { return player; }
	class AAIEnemy1* GetCharacter(void) { return character; }

	void SetCharacter(class AAIEnemy1* a_Character) { character = a_Character; }

private:
	FiniteStateMachineAI1* fsm = nullptr;

	AActor* player = nullptr;
	class AAIEnemy1* character = nullptr;
};
