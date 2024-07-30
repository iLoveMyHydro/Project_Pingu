// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerAI1.generated.h"

class FiniteStateMachineAI1;

/**
 * 
 */
UCLASS()
class AAIControllerAI1 : public AAIController
{
	GENERATED_BODY()

public:

	AAIControllerAI1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetPlayer(void) const { return Player; }
	class AAIEnemy1* GetCharacterAI(void) const { return Character; };

	void SetCharacter(class AAIEnemy1* A_Character) { Character = A_Character; }

private:

	UFUNCTION()
	void AttackPlayer(AActor* OtherActor, FAIStimulus Stimulus);

	const FString PERCEPTION_NAME = FString(TEXT("Perception Component"));


	UPROPERTY(EditAnywhere, DisplayName = "Respawn Delay", Category = "Respawn")
	float RespawnDelay = 2;

	UPROPERTY(EditAnywhere, DisplayName = "Respawn Timer Handle", Category = "Respawn")
	FTimerHandle RespawnTimerHandle;

	FiniteStateMachineAI1* Fsm = nullptr;
	AActor* Player = nullptr;
	class AAIEnemy1* Character = nullptr;
	UAIPerceptionComponent* PerceptionComponent = nullptr;
};
