// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

class NormalFSM;
/**
 * 
 */
UCLASS()
class ABossAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABossAIController();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetPlayer(void) const { return Player; }
	class ABossEnemy* GetCharacterAI(void) const { return Character; };

	void SetCharacter(class ABossEnemy* A_Character) { Character = A_Character; };


private:
	const FString PERCEPTION_NAME = FString(TEXT("Perception Component"));

	NormalFSM* Fsm = nullptr;
	AActor* Player = nullptr;
	class ABossEnemy* Character = nullptr;
};
