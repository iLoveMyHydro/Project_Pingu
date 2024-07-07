// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine/FSM/FiniteStateMachineAIBoss1.h"

/**
 * 
 */
class SimpleFSMBossAI1 : public FiniteStateMachineAIBoss1
{
public:
	inline SimpleFSMBossAI1(AAIControllerAIBoss1* A_Controller) : FiniteStateMachineAIBoss1(A_Controller) {};
	inline ~SimpleFSMBossAI1() {};

	virtual void Initialize() override;

	StateBossAI1* GetSearchPlayerState(void) const { return SearchPlayerState; }
	StateBossAI1* GetThrowObjectState(void) const { return ThrowObjectState; }
	StateBossAI1* GetThrowManyObjectsState(void) const { return ThrowManyObjectsState; }
	StateBossAI1* GetThrowBouncingObjectState(void) const { return ThrowBouncingObjectState; }
	StateBossAI1* GetWaitState(void) const { return WaitState; }

private:
	const FString SEARCH_PLAYER_STATE = TEXT("Search Player State");
	const FString THROW_OBJECT_STATE = TEXT("Throw Object State");
	const FString THROW_MANY_OBJECTS_STATE = TEXT("Throw Many Objects State");
	const FString THROW_BOUNCING_OBJECTS_STATE = TEXT("Throw Bouncing Objects State");
	const FString WAIT_STATE = TEXT("Wait State");

	//States
	StateBossAI1* SearchPlayerState = nullptr;
	StateBossAI1* ThrowObjectState = nullptr;
	StateBossAI1* ThrowManyObjectsState = nullptr;
	StateBossAI1* ThrowBouncingObjectState = nullptr;
	StateBossAI1* WaitState = nullptr;
};
