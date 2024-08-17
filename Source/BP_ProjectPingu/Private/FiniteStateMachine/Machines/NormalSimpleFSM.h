// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/NormalFSM.h"

/**
 * 
 */
class NormalSimpleFSM : public NormalFSM
{
public:
	// Constructor for the Normal Controller
	inline NormalSimpleFSM(ANormalAIController* A_Controller) : NormalFSM(A_Controller) {};

	// Constructor for the Boss Controller
	inline NormalSimpleFSM(ABossAIController* A_Controller) : NormalFSM(A_Controller) {};

	// Deconstructor
	inline ~NormalSimpleFSM() {};

	// Initialize the FSM
	virtual void Initialize() override;

	// Sets the States
	NormalStateAI* GetSearchPlayerState(void) const { return SearchPlayerState; }
	NormalStateAI* GetThrowObjectState(void) const { return ThrowObjectState; }
	NormalStateAI* GetBossThrowObjectState(void) const { return BossThrowObjectState; }
	NormalStateAI* GetThrowFastObjectsState(void) const { return ThrowFastObjectsState; }


private:
	const FString SEARCH_PLAYER_STATE = FString(TEXT("Search Player State"));
	const FString THROW_OBJECT_STATE = FString(TEXT("Throw Object State"));
	const FString THROW_FAST_OBJECTS_STATE = FString(TEXT("Throw Fast Objects State"));
	const FString BOSS_THROW_OBJECT_STATE = FString(TEXT("Boss Throw Object State"));

	//States
	NormalStateAI* SearchPlayerState = nullptr;
	NormalStateAI* ThrowObjectState = nullptr;
	NormalStateAI* ThrowFastObjectsState = nullptr;
	NormalStateAI* BossThrowObjectState = nullptr;
};
