// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NormalAIController.generated.h"

class NormalFSM;

/**
 *
 */
UCLASS()
class ANormalAIController : public AAIController
{
	GENERATED_BODY()

public:

	ANormalAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets the Player for the FSM
	AActor* GetPlayer(void) const { return Player; }

	// Gets the Normal Enemy
	class ANormalEnemy* GetCharacterAI(void) const { return Character; };

	// Sets the Character for the Normal Enemy
	void SetCharacter(class ANormalEnemy* A_Character) { Character = A_Character; };


private:
	const FString PERCEPTION_NAME = FString(TEXT("Perception Component"));

	// FSM for the Normal Enemy
	NormalFSM* Fsm = nullptr;
	AActor* Player = nullptr;
	class ANormalEnemy* Character = nullptr;
};
